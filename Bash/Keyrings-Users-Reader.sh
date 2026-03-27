#!/bin/bash
# Dump all user keys from /proc/keys by fixing the Hex formatting

echo "[*] Hunting for 'user' keys in /proc/keys..."

# Extract lines containing the 'user' type
grep -w 'user' /proc/keys | while read -r line; do
    id_hex=$(echo "$line" | awk '{print $1}')
    desc=$(echo "$line" | awk '{print $NF}')
    
    echo "[*] Attempting to dump key 0x$id_hex ($desc) ..."
    
    # The fix: Adding '0x' before the hex ID so keyctl understands it
    keyctl pipe "0x$id_hex" > "dump_${id_hex}.bin" 2>/dev/null
    
    # Check if the output file actually contains data (-s flag)
    if [ -s "dump_${id_hex}.bin" ]; then
        echo "  [+] Success! Saved to dump_${id_hex}.bin"
        
        # Try to print a readable text preview without breaking the terminal
        echo -n "  [+] Text preview: "
        keyctl print "0x$id_hex" 2>/dev/null || echo "[Binary Data]"
    else
        echo "  [-] Failed (Permission Denied, Revoked, or Empty)."
        # Clean up the empty file so you only keep successful dumps
        rm -f "dump_${id_hex}.bin"
    fi
done

echo "[*] Done."
