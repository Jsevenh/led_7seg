import sys

def process_files(input_pio,input_c):
    with open(input_pio, 'r') as pio_file:
        pio_content = pio_file.readlines()
        
    # Find the index of the line containing '%'
    for i, line in enumerate(pio_content):
        if '%' in line:
            # Remove all lines after the line containing '%', including the line itself
            pio_content = pio_content[:i]
            # Write back the filtered content to the .pio file
            with open(input_pio, 'w') as pio_file:
                pio_file.writelines(pio_content)
            break

    with open(input_pio,'a') as pio_file:
        pio_file.write("\n% c-sdk {\n")
        
        with open(input_c,'r') as c_file:
            for line in c_file:
                # # do not include #include statements 
                # if not line.startswith('#') and '#' not in line:
                    pio_file.write(line)
        pio_file.write("\n%}\n")
    
    
if __name__=="__main__":
   
    if len(sys.argv) != 3:
        print("Usage: python process_files.py <input_pio> <input_c>")
        sys.exit(1)
    # pio file
    pio=sys.argv[1]
    # c file
    c=sys.argv[2]
    process_files(pio,c)
    
    
    
    