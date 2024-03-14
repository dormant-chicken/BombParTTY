# BombParTTY

## About

BombParTTY - A word game in the terminal inspired by the popular multiplayer game 'BombParty'

If you don't know what BombParty is, go [here](https://jklm.fun/)

you can learn how to play by watching other people in a game without joining

<br>

## Installation

### Dependencies

* ncurses

### newest git

clone this repository:

```
git clone https://github.com/dormant-chicken/BombParTTY
```

then, change your directory

```
cd BombParTTY/
```

compile the program:

```
make all
```

make the program executable from any directory:

```
sudo make install
```

## Makefile options

change your directory if not already inside:

```
cd BombParTTY/
```

### Uninstall

this will remove all the files that were installed

```
sudo make uninstall
```

### Reinstall

```
sudo make reinstall
```

## Usage

after compiling and installing, just run 'bomb-partty' from the terminal to run the program:

```
bomb-partty
```

### Options

These are the available arguments:

`--bypass-term-height`

`--bypass-term-width`

These will bypass the terminal size checks, but might cause rendering problems

## Custom word list

if you want a custom word list, edit the `dictionary.txt` file before running `sudo make install`

you can also completely make a new list, as the program will adjust to the file

I got this file from my `/usr/share/dict/` directory, which is a Unix standard, read [here](https://en.wikipedia.org/wiki/Words_(Unix)) if you want to learn more

## Custom letter set

the letter set is the combination of letters that the input must contain (they appear at the center of the screen)

If you want a custom letter set, edit the `set.txt` file before running `sudo make install`

I created the letter set file using a script
