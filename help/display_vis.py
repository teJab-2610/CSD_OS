import sys

def main():
    filepath = "../../src/drivers/memory.txt"
    outfile = "./memory_out.txt"

    try:
        with open(filepath, 'r') as file, open(outfile, 'w') as sys.stdout:
            c = 0

            for line in file:
                if len(line.strip()) > 1:
                    line = ''.join(' ' if char == '0' else '*' for char in line.strip())
                    print(line, end='')
                    c += 1

                if c == 80:
                    print()
                    c = 0

    except IOError as e:
        print(f"Error: Could not open file {filepath}", file=sys.stderr)
        return 1

if __name__ == "__main__":
    main()