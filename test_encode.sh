#! /bin/sh

input_file="lorem_ipsum.txt"
output_file="data.txt"
packet_dir="packets/"

cat "$input_file" | ./encode

# delete out file if it exists
[ -e "$output_file" ] && rm "$output_file"

# will not sort correctly for long packet names
files=$(ls "$packet_dir"*.hoff | sort -n -t '.' -k 1)
for file in $files; do
    ./decode "$file" >> "$output_file"
done

# verify that there is no difference between original file and reconstructed packets
diff "$input_file" "$output_file"

# cleanup
rm -f "$output_file"
./clean_pkts.sh