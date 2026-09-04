# what-i-know-about-openstep

Learnings about developing for OPENSTEP 4.2, macOS' non-Apple predecessor.

**Background:** Although I'm a statistician, I do like tinkering with old computers -- including programming for them in classic C. Although modern R is a resource hog, it's easy to forget how capable old computers can be without the cruft! I am not an experienced developer, and I don't have any pretentions to making high-quality software. I use AI a lot to explore and solve problems (I don't have the time to do a lot of research myself, especially when the vagaries of C89 vs. C99 come into play!) But, as a good statistician, I'm committed to quality and rigor: I know that what I *output* I need to check, understand, and be able to answer questions for on the spot!

**This project:** Things that might be useful to people developing for OPENSTEP. Including:

1. `GETTING-STARTED.md`: a guide (and quick reference) to the OPENSTEP Unix environment; how to set up a headless OPENSTEP host to do development. **As provided here, the specific credentials, IP, port for connecting to the guest are mine -- read through and edit! It's short.**

2. `UNIX-ENVIRONMENT`: in-depth guides to the Unix environment available on the guest; `UNIX-ENVIRONMENT.md` documents general things to remember; the sub-folder `UNIX-ENVIRONMENT/SKILLS` presents guides to doing various Unix-y tasks that an AI agent might do.

3. `REFERENCES/MANPAGES`: raw manpages from OPENSTEP 4.2. Additionally:

	1. `.../MANPAGES/SECTIONS.md` lists (sub)sections of the manual, their purpose, and where to find them;

	2. `.../MANPAGES/whatis` is the OPENSTEP 4.2 `whatis` index (i.e. synopses of manpages.)
	
4. `REFERENCES/FRAMEWORKS`: Resources for Objective-C frameworks, organized by framework name.
	
	- Some frameworks: `Foundation.framework` (the Objective-C "standard" library); `AppKit.framework` (the OPENSTEP UI application development framework); `SoundKit.framework` (audio streaming-playing-recording; useful widgets); `NEXTIME.framework` (similarly for video.) More included.
	
	- Subfolder structure: `*.framework/Reference` provides HTML documentation; `*.framework/Headers` provides Objective-C headers; `*.framework/Examples` provides examples.

6. `REFERENCES/C-HEADERS`: headers for core C libraries; highlights include the ANSI C stdlib (`ansi`), Objective-C runtime (`objc`), native Mach API (`mach`), 4.2 BSD-derived/Unix headers (`bsd`), etc.

7. `REFERENCES/OPENSTEP-94`: an HTML version of the 1994 OPENSTEP specification (originally provided as RTF), graciously made available by the [GNUstep project.](https://www.gnustep.org/developers/documentation.html). Although this information duplicates much of what is available in `REFERENCES/FRAMEWORKS`, especially for Foundation and AppKit, the Display PostScript documentation is invaluable (`.../OPENSTEP-94/DisplayPostScript`). As well as the various indexes.

## Licensing

All text I've created public domain. Historic OPENSTEP/NeXT content provided "as-is".
