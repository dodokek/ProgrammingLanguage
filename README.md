# Programming Language
This is an implementation of my own programming language. 
Notice, that AST tree is built according to <a href="https://github.com/dodokek/LanguageStandart">our own standart</a>.
## Overview
In this project I will translate instructions, written on my custom language to binary file. It can be executed with my own *CPU implementation*. In my <a href="https://github.com/dodokek/BinaryTranslator"> Binary translator </a> project this binary file is translated into *.elf* file.  

## How it works

###  Writing program with custom language
Heres an example of program, written on *Meow meow script*:
~~~
комната_единички >маин ( )
    нюх_нюх >бобер 1     мяу
    нюх_нюх >текущ 1     мяу
    нюх_нюх >топчик 0    мяу
    слизнуть ( >топчик ) мяу

    нюх_нюх >бобер кис_кис >фак ( >бобер >текущ >топчик ) мяу
    буэээ ( >бобер ) мяу
    лее_куда_прешь ( )  мяу
валим

комната_единички >фак ( >верх >сус >рез )
    
    нюх_нюх >сус >сус сожрать 1 мяу
    нюх_нюх >рез >рез мяя >сус мяу
    нюх_нюх >бобер 123 мяу

    куда_епта >сус пахнет_знакомо >верх
        лее_куда_прешь ( >рез ) мяу
    валим
    ай_ладно
        нюх_нюх >рез кис_кис >фак ( >рез >сус >верх ) мяу
    валим
    лее_куда_прешь ( >рез ) мяу

валим
~~~
> Program finds factorial of number, given by user.

### Frontend - parsing 

Using **recursive descent** input file is parsed into *AST tree*.
The result of parsing you can see on this image:
![image](https://github.com/dodokek/ProgrammingLanguage/assets/57039216/cce5aa05-adc7-4467-8a35-519a0384db5d)

### Frontend - Writing AST tree on disk

After parsing code to AST tree, program is not translating it into assembly code. It writes it into .txt file instead, to save the tree image in easy-to-access format. 

This is done mostly in educational purposes. With the help of <a href="https://github.com/dodokek/LanguageStandart">language standart</a> we are capable of generating executable files from different programming languages if they *support* such language standart. 

Here is some of my colleagues, whose programming language I can handle: <a href="https://github.com/mr-gukas"> MrGukas </a>, <a href="https://github.com/aleksplast">AleksPlast</a>, <a href="https://github.com/lexain12"> Tyazhelkov Victor </a>, and 4+ more. 

Example of AST tree image in *.txt* file:

~~~
{  ST  {  FUNC  { "main" { NIL } { VOID }  }  {  ST  {  VAR  { "zho" }  { 3802 }  }  {  ST  {  VAR  { "pk" }  { 2083 }  }  {  ST  {  VAR  { "a" }  { 1 }  }  {  ST  {  VAR  { "b" }  { 2 }  }  { ...
~~~

### Backend - Translating AST tree into assembly 

I build AST tree from *tree.txt* file, according to language standart.
After that, tree is being translated into *Sequence of Assembly commands*. 
> Note: in this project I implemented my own assembly and CPU work.

Example of generated assembly code:

~~~
call main 
hlt

; let the chaos begin

; function 
main:
in

push [rax+2]
push [rax+1]

...

out
ret
end
~~~

### Executing the code

After we get assembly file, we can execute it with *CPU work implementation* wich is integrated in this project.

You can see more detailed explanation of this process <a href="https://github.com/dodokek/Processor">here</a>.

## Conclusion

This project gave me a ton of knowledge about parsing algorithms and structures. Also I got a unique experience in developing my own language standart with my colleagues. In the end of the 1st year of education in MIPT this project become 100% real programming language, because it is now capable of generating .elf file. See its <a href="https://github.com/dodokek/BinaryTranslator">improved version here</a>.
