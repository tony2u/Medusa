1.Rename infblock.c "border" to "ft_border" so that to avoid conflict with 
In file included from /Users/fjz/Documents/MAC/Medusa/Engine/External/freetype/src/gzip/ftgzip.c:94:
Medusa/Engine/External/freetype/src/gzip/infblock.c:18:18: error: redefinition of 'border' as different kind of symbol
local const uInt border[] = { /* Order of the bit length code lengths */
                 ^
In module 'Darwin' imported from ../../include/freetype/config/ftstdlib.h:36:
/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator9.0.sdk/usr/include/curses.h:536:28: note: previous definition is here
extern NCURSES_EXPORT(int) border (chtype,chtype,chtype,chtype,chtype,chtype,chtype,chtype);    /* generated */
                           ^
In file included from /Users/fjz/Documents/MAC/Medusa/Engine/External/freetype/src/gzip/ftgzip.c:94:
/Users/fjz/Documents/MAC/Medusa/Engine/External/freetype/src/gzip/infblock.c:242:28: error: use of undeclared identifier 'border'
        s->sub.trees.blens[border[s->sub.trees.index++]] = (uInt)b & 7;
                           ^
/Users/fjz/Documents/MAC/Medusa/Engine/External/freetype/src/gzip/infblock.c:246:28: error: use of undeclared identifier 'border'
        s->sub.trees.blens[border[s->sub.trees.index++]] = 0;
