# Howto: convert an RTF/RTFD documentation tree to HTML

**Purpose:** Step-by-step instructions for converting an RTF/RTFD documentation tree to HTML.

**Requirements:** Use macOS `textutil`, Ghostscript (`gs`), Poppler (`pdftocairo`), and Python with Pillow. 

**Motivation:* NeXTSTEP documentation is often delivered as a tree of RTF/RTFD files,
which in turn reference EPS vectors or TIFF rasters. For modern users, we convert
these documentation trees to HTML, SVG, and JPG, and delete original files.

**Safety instructions:** Work on a copy, or retain a compressed archive of the originals. Set `ROOT` to the documentation folder. Do not follow symlinks outside that folder or overwrite existing outputs without checking them.

## Step-by-step instructions

1. **Convert each document beside its source.** Treat each `.rtfd` directory as one document and prune its descendants from the conversion walk, so its internal `TXT.rtf` is not converted separately. Also collect standalone `.rtf` files. For each source:

   ```sh
   html="${source%.*}.html"
   textutil -convert html -encoding UTF-8 -output "$html" "$source"
   ```

   Thus `Example.rtfd` produces adjacent `Example.html`. Record failures and retain every source until the entire conversion has passed validation.

2. **Resolve the HTML's attachment references.** Inspect `<object data="…">` and `<img src="…">`. `textutil` can emit incorrect URLs such as `file:///drawing.eps`. URL-decode the filename, locate it in the corresponding RTFD bundle, and replace the URL with an escaped, relative path, e.g. `Example.rtfd/drawing.eps`. Resolve ambiguous names within the document's own bundle rather than guessing across the tree.

3. **Convert referenced EPS files to adjacent SVG files.** Use a temporary PDF as the intermediate; preserve the EPS bounding box and disable automatic rotation:

   ```sh
   svg="${eps%.*}.svg"
   tmpdir=$(mktemp -d)
   gs -dSAFER -dBATCH -dNOPAUSE -dEPSCrop \
     -dAutoRotatePages=/None -sDEVICE=pdfwrite \
     -dCompatibilityLevel=1.7 -dEmbedAllFonts=true \
     -sOutputFile="$tmpdir/artwork.pdf" -f "$eps" &&
     pdftocairo -svg "$tmpdir/artwork.pdf" "$svg"
   ```

   Check the result before removing the temporary PDF and directory. This preserves vector paths and embeds any raster content. Identical EPS files can be converted once by SHA-256 and their SVG copied to each location. Inspect font-substitution warnings: our conversion substituted Helvetica-Narrow-Bold for missing TradeGothic-BoldCondTwenty.

4. **Replace EPS objects with actual inline SVG markup.** Parse each converted SVG and insert its root `<svg>…</svg>` in place of the entire corresponding `<object>…</object>`. Omit the SVG file's XML declaration and doctype. Preserve `viewBox`, width, and height; use `style="max-width:100%;height:auto"`. Prefix every SVG ID uniquely per insertion and update its fragment references, including `href`, `xlink:href`, and `url(#…)`, to prevent collisions between diagrams. Add an accessible `<title>`. An optional relative `data-source="…svg"` records provenance but does not load the artwork. Use `<!DOCTYPE html>` for these pages.

5. **Convert referenced TIFF images to adjacent JPG files and update HTML.** Preserve pixel dimensions. Decode with Pillow, retain grayscale (`L`) or RGB, and flatten any transparency onto white before saving:

   ```python
   image.save(jpg_path, "JPEG", quality=85, optimize=True, subsampling=0)
   ```

   If Pillow cannot read an older TIFF, decode it to a temporary PNG with `sips -s format png "$tiff" --out "$temporary_png"`, then use Pillow. Update the HTML's image URLs and filename-based alt text to `.jpg`. We also converted unreferenced TIFF copies and hidden `.dir.tiff` icons. JPEG is lossy and may be larger than these already compressed TIFF screenshots; do not assume this step saves space.

6. **Validate before deleting sources.** Check every conversion succeeded, every local HTML/SVG resource reference resolves, and no resource still depends on RTF, EPS, or TIFF. Check SVGs for external dependencies and duplicate IDs, decode every JPG, and visually inspect representative HTML pages and each distinct graphic. Preserve explanatory prose and code examples mentioning `.tiff`; those are not attachment references.

7. **Delete only source files, retaining all directories.** After validation and with the original archive retained:

   ```sh
   find "$ROOT" -type f \( \
     -iname '*.rtf' -o -iname '*.eps' -o \
     -iname '*.tif' -o -iname '*.tiff' \
   \) -delete
   ```

   This removes standalone and RTFD-internal RTF files, plus original EPS/TIFF files, without deleting `.rtfd` directories or their HTML/SVG/JPG assets. The remaining bundles are no longer complete original RTFD documents. Recheck local references and confirm the directory structure is unchanged.
