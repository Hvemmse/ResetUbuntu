## ResetUbuntu
a little tool to start from scratch and reset the gnome settings to default

there is a tool for the english version and the dansih version.
<code>
g++ -o resetubuntuuk resetubuntuuk.cpp `pkg-config --cflags --libs gtk+-3.0`
</code>
or
<code>
g++ -o resetubuntu resetubuntu.cpp `pkg-config --cflags --libs gtk+-3.0` 
</code>

for the danish verson
