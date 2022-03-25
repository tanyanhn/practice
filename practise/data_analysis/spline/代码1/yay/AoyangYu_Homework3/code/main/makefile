#这是aaaa第一个要编译的c文件
aaa =b.cpp
#这是bbbb第二个要编译的c文件
bbb=*2.cpp
#这是cccc第三个要编译的c文件
ccc=*3.cpp

#this is the first file need to compile
nnn=*.tex
#this is the second file need to compile
ooo=mai.tex
#this is the third file need to compile
ppp=mae.tex

aa=a
aaaa=ga

bb=b
bbbb=gb

cc=c
cccc=gc

zz=z
gzz=gz

zzz=zh
gzzz=g2z

ddd=$(aaa) $(bbb)

eee=$(aaa) $(bbb) $(ccc)

$(aa):$(aaa)
	g++ $<  -o $@
$(bb):$(bbb)
	g++ $<  -o $@
$(cc):$(ccc)
	g++ $<  -o $@

$(zz):$(ddd)
	g++ $^ -o $@
$(zzz):$(eee)
	g++ $^ -o $@

$(aaaa):$(aaa)
	g++ -g  $<  -o $@

$(bbbb):$(bbb)
	g++ -g  $<  -o $@
$(cccc):$(ccc)
	g++ -g  $<  -o $@
$(gzz):$(ddd)
	g++ -g  $^  -o $@
$(gzzz):$(eee)
	g++ -g  $^  -o $@
aa:$(aa)
	./$<
gaa:$(aaaa)
	./$<
ta:$(aaaa)
	gdb $<
va:$(aaaa)
	valgrind --leak-check=full ./$<
bb:$(bb)
	./$< 
gbb:$(bbbb)
	./$< 
tb: $(bbbb)
	gdb $<
vb:$(bbbb)
	valgrind --leak-check=full ./$<

cc:$(cc)
	./$< 
gcc:$(cccc)
	./$< 
tc: $(cccc)
	gdb$<
vc:$(cccc)
	valgrind --leak-check=full ./$<
zz:$(zz)
	./$< 
gzz:$(gzz)
	./$< 
tz:$(gzz)
	gdb $< 
zzz:$(zzz)
	./$< 
gzzz:$(gzzz)
	./$< 
tzz:$(gzzz)
	gdb  $< 


caa:
	rm -r $(aa)
cga:
	rm -r $(aaaa)
cbb:
	rm -r $(bb)
cgb:
	rm -r $(bbbb)
ccc:
	rm -r $(cc)
cgc:
	rm -r $(cccc)
czz:
	rm -r $(zz)
cgz:
	rm -r $(gzz)
czzz:
	rm -r $(zzz)
cgzz:
	rm -r $(gzzz)



clatex:
	rm -r *.aux  *.fls  *.log  *.fdb_latexmk  *.synctex.gz	*.out

xn:$(nnn) 
	xelatex ./$<
	rm -r *.aux  *.fls  *.log  *.fdb_latexmk  

pn:$(nnn)
	pdflatex ./$<
	rm -r *.aux  *.fls  *.log  *.fdb_latexmk  
xo:$(ooo) 
	xelatex ./$<
	rm -r *.aux  *.fls  *.log  *.fdb_latexmk  

po:$(ooo)
	pdflatex ./$<
	rm -r *.aux  *.fls  *.log  *.fdb_latexmk  
xp:$(ppp) 
	xelatex ./$<
	rm -r *.aux  *.fls  *.log  *.fdb_latexmk  

pp:$(ppp)
	pdflatex ./$<
	rm -r *.aux  *.fls  *.log  *.fdb_latexmk  
