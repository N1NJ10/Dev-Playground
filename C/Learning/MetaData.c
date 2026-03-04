#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h> // Required for the struct stat and fstat()

// 1. Define what our database header looks like
struct db_header {
    int magic_number;  // A signature so we know it's our file format
    int claimed_size;  // How big the file *claims* to be
};

// A quick helper function to print using raw syscalls
void print_out(const char *msg, int len) {
    write(1, msg, len);
}

int main() {
    /* =========================================================
       PHASE 1: THE ATTACKER (Creating a poisoned file)
       ========================================================= */
    int fd = open("poisoned.db", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    
    struct db_header fake_header;
    fake_header.magic_number = 0x4442; // Hex for "DB"
    
    // THE LIE: We tell the header this file is 100,000 bytes long.
    // If a program trusts this, it will allocate too much memory.
    fake_header.claimed_size = 100000; 

    // Write the 8-byte header, plus 4 bytes of dummy data.
    // The total physical size on disk will only be 12 bytes.
    write(fd, &fake_header, sizeof(fake_header));
    write(fd, "HAX!", 4);
    close(fd);


    /* =========================================================
       PHASE 2: THE DEFENDER (Validating with fstat)
       ========================================================= */
    print_out("[*] Opening database...\n", 24);
    
    // Grab a read token from the kernel
    fd = open("poisoned.db", O_RDONLY);
    if (fd == -1) return 1;

    // 1. Read what the file CLAIMS
    struct db_header read_header;
    read(fd, &read_header, sizeof(read_header));

    // 2. Ask the kernel for the TRUTH
    // We create the empty struct, then pass its memory address (&) to fstat
    struct stat physical_truth;
    fstat(fd, &physical_truth); 

    // 3. The Interrogation
    // physical_truth.st_size contains the exact byte count from the hard drive
    if (read_header.claimed_size != physical_truth.st_size) {
        
        // The sizes don't match. 100000 != 12. We caught the lie.
        print_out("[!] HACKER DETECTED! Header size does not match physical disk size.\n", 69);
        
        close(fd);
        return 1; // Terminate immediately to prevent memory corruption
    }

    // If we make it here, the file was safe.
    print_out("[+] File is perfectly valid and safe to allocate.\n", 50);
    close(fd);
    
    return 0;
}