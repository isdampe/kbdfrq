import sys, json

def main(argc, argv):
    if argc < 2:
        print("Usage: chart.py log_file.json")
        exit(1)

    f = open(argv[argc -1])
    if not f:
        print("Could not read %s" % argv[argc -1])
        exit(1)

    buffer = f.read()
    f.close()

    lines = buffer.split("\n")
    ourLine = None

    i = len(lines) -1
    while i >= 0:
        ourLine = lines[i]
        if ourLine:
            break
        i -= 1

    idx = ourLine.find("\":")
    if idx < 0:
        print("Couldn't find ':' separator. Is the file valid JSON logs?'")
        exit(1)

    ourLine = (ourLine[idx + 2:]).strip()
    data = json.loads(ourLine)

main(len(sys.argv), sys.argv)
