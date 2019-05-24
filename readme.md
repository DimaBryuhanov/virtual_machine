### To run and compile:
```
gcc -Wall -Wextra -o main main.c && ./main
```


### To see the program.vm in hex:
```
xxd program.vm
```

### To install wat2wasm (converts Web Assembly Text (wat) to WASM):
```
sudo npm i wat2wasm -g
```

### To compile a .wat file to .wasm:
```
wat2wasm test.wat
```