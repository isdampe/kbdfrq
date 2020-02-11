# kbdfrq
A super simple keypress frequency recorder for linux.

## Building

```bash
cd kbdfrq
make
```

## Running

```bash
sudo ./bin/kbdfrq
```

Your logs will appear in the current directory using the format `m-d-Y.json`. 

The files are not true JSON, but each line represents a JSON object in the format

`YYYY-MM-DD HH:MM:SS=[JSON_OBJECT]`
