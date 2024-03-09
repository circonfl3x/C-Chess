# C-Chess

C-Chess is a chess game made completely in vanilla C + raylib.

## How to run
you can build it using the Makefile by simply doing `make clean ; make` and that will give you a binary named chess. For manual compilation, it is dependent on raylib it doesn't need `-lm` as it is in the Makefile,
but I just included it incase I will need it.

## NOTHING SPECIAL
I don't even think this could even be called a game as of now. There are a lot of chess features not implemented as of right now, but I tried as hardest to at least make it similar to an OOB experience.

## What works
- Movement of pieces as they are supposed to and rules around movements (though I haven't extensively tested this so it may be buggy)
- Pieces' paths can be blocked by other pieces (except for knights of course) so you can't just phase across pieces
- Correct system of eating pieces for each piece (even the pawn) and pieces cannot eat each other *shock*

## What doesn't work
- Castling
- Check and Checkmate (and anything to do with putting the king in danger)
- sounds? Animations? (if you care about those)
- en passant
- Game rules (white and black turns, 3 move draw, and those already listed above e.t.c.)
And more that I can't think off from the top of my head but will add here as time goes on

## Boring information
This has been built on aarch64 on both macOS and Linux (fedora). An interesting thing I noted on Linux is that there is always a leak of 2216 bytes, I couldn't verify this on macOS because I couldn't get asan to run
because... well... macOS. I'm not sure at the moment but it seems more to be related to the asahi linux drivers? Because it is leaking in places only god knows where. Because any raylib project that doesn't leak memory
will always leak 2216 bytes on my asahi linux install. Anyway, I haven't tested it on an x86 build target and I'm too lazy to create an x86 virtual machine soooo.... 

