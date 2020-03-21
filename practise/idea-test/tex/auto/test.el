(TeX-add-style-hook
 "test"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("book" "a4paper")))
   (add-to-list 'LaTeX-verbatim-environments-local "lstlisting")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "lstinline")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "lstinline")
   (TeX-run-style-hooks
    "latex2e"
    "book"
    "bk10"
    "geometry"
    "marginfix"
    "amsfonts"
    "amsmath"
    "amssymb"
    "amsthm"
    "ctex"
    "enumerate"
    "graphicx"
    "layout"
    "multicol"
    "mathrsfs"
    "fancyhdr"
    "subfigure"
    "tcolorbox"
    "tikz-cd"
    "listings"
    "xcolor"
    "braket")
   (TeX-add-symbols
    '("Dist" 2)
    '("ccg" 1)
    '("voidenvironment" 1)
    '("grb" 1)
    '("avg" 1)
    '("difPy" 1)
    '("difPx" 1)
    '("gen" 1)
    "dif"
    "Dim"
    "sgn"
    "Span"
    "dom"
    "Arity"
    "Int"
    "Ext"
    "Cl"
    "Fr"
    "rank"
    "Iden"
    "ii"
    "Rez"
    "Imz"
    "pcp"
    "Log"
    "Arg"
    "Null"
    "Range"
    "Ker"
    "Iso"
    "Aut"
    "ord"
    "Res"
    "GL"
    "SL"
    "tbbint"
    "tbint"
    "dbbint"
    "dbint"
    "bint"
    "bbint")
   (LaTeX-add-environments
    "solution")
   (LaTeX-add-amsthm-newtheorems
    "thm"
    "axm"
    "alg"
    "asm"
    "defn"
    "prop"
    "rul"
    "coro"
    "lem"
    "exm"
    "rem"
    "exc"
    "frm"
    "ntn"
    "rmk"))
 :latex)

