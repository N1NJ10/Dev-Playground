#include <unistd.h>
#include <fcntl.h>

int main() {
    char buffer[1024];
    ssize_t bytes_captured;

    // Prompt the user using FD 1 (stdout)
    write(1, "Enter the data you want to save: ", 33);

    // 1. The Intake: Pull raw bytes from FD 0 (stdin)
    bytes_captured = read(0, buffer, sizeof(buffer));

    // Number of bytes With the terminator \n
    printf("Number of bytes read: %d\n", bytes_captured);

    // If read fails or gets an EOF immediately, exit cleanly
    if (bytes_captured <= 0) return 1;

    // Strip the trailing newline so the '!' appends directly to the text
    if (buffer[bytes_captured - 1] == '\n') {
        bytes_captured--;
    }

    // 2. File Creation: Command the kernel to open/create the file
    // O_CREAT: Create if it doesn't exist
    // O_WRONLY: Write mode only
    // O_TRUNC: Wipe it clean if it already exists
    // 0644: Standard read/write permissions
    int fd = open("loot.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) return 1;

    // 3. Put the data into the file using our new FD
    write(fd, buffer, bytes_captured);

    // 4. Add '!' at the end
    write(fd, "!\n", 2);

    // 5. Relinquish the write token
    close(fd);

    // 6. The Verification: Re-open the file in Read-Only mode to print it
    write(1, "\n[+] File Context:\n", 19);

    // Grab a new token for reading
    fd = open("loot.txt", O_RDONLY);
    if (fd == -1) return 1;

    // Trap the file descriptor in a loop until it returns 0 (EOF)
    while ((bytes_captured = read(fd, buffer, sizeof(buffer))) > 0) {
        // Blast the exact bytes we read directly to standard output
        write(1, buffer, bytes_captured);
    }

    // Final cleanup
    close(fd);

    return 0;
}