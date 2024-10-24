import re

def parse_verilog_file(filename):
    with open(filename, 'r') as f:
        content = f.read()

    maps = {
        'regularMap': {},
        'shiftMap': {},
        'ctrlMap': {},
        'extendMap': {}
    }

    current_map = None
    for line in content.split('\n'):
        if 'if (extend)' in line:
            current_map = 'extendMap'
        elif 'else if (ctrl)' in line:
            current_map = 'ctrlMap'
        elif 'else if (shift)' in line:
            current_map = 'shiftMap'
        elif 'else begin' in line:
            current_map = 'regularMap'
        
        match = re.search(r"8'h([0-9a-fA-F]{2}):\s*ascii\s*<=\s*8'h([0-9a-fA-F]{2})", line)
        if match and current_map:
            scancode, ascii_code = match.groups()
            maps[current_map][int(ascii_code, 16)] = int(scancode, 16)

    return maps

def generate_c_array(name, map_dict):
    print(name)
    max_scancode = max(max(map_dict.keys()), 0xFF)  # Ensure at least 256 elements
    array = ['0x2E'] * (max_scancode + 1)  # Initialize with 0x2E (ASCII for '.')
    for scancode, ascii_code in map_dict.items():
        array[scancode] = f'0x{ascii_code:02X}'
    
    array_str = ', '.join(array)
    return f"const uint8_t {name}[{len(array)}] = {{{array_str}}};"

def write_header_file(filename, maps):
    with open(filename, 'w') as f:
        f.write("#ifndef PS2_SCANCODE_MAP_H\n")
        f.write("#define PS2_SCANCODE_MAP_H\n\n")
        f.write("#include <stdint.h>\n\n")
        
        for name, map_dict in maps.items():
            f.write(generate_c_array(name, map_dict))
            f.write("\n\n")
        
        f.write("#endif // PS2_SCANCODE_MAP_H\n")

if __name__ == "__main__":
    input_file = "scancodes.v"
    output_file = "test.h"
    
    maps = parse_verilog_file(input_file)
    write_header_file(output_file, maps)
    print(f"Header file '{output_file}' has been generated successfully.")