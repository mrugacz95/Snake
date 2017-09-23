#### Installation
```
sudo apt-get install liballegro4-dev
```
### Compilation
```
gcc main.c alinit.c game.c snake.c -o game $(allegro-config --libs)
```
### Running
```
./game
```
