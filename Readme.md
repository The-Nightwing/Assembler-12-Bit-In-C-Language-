This is a 12 Bit Assembler.
I have used C language to make the Assembler.

Comments in Test file:
    Both single line comments and block line comments in the test file are removed from the test file, then Pass1 
    and Pass2 is implemented.


Error Reporting:
Three types of errors are reported in the file:
    a)If more than one operand is supplied.
    b)Wrong Opcode encountered.
    c)If No STP command is found.
    d)if any operand value is greater than or equal to 256 it will throw an error, as only 8 bits can be generated for operand
    and no objectFile will be made.
    e)If more than One operand is supplied,it will throw an error and no objectFile will be made.

Error Handling:
    Except a) ,other two errors are handled.
    In a) part, the terminal will give output that this is a fatal error, and No object file will be formed.
    For d),it will throw an error that Memory Address Out of Bounds(>=256).
    For e),it will show Fatal Error,More than One Operand Passed.


Format:
    a) While reading labels from the file , Labelname with ":" and without ":", both are treated as labels.If label is used as a 
    operand then ":" has to be used too if the label name contains ":" while writing it as a operand otherwise it will be 
    considered as a symbol by the assembler.
    b)After BRN and BRZ (branch opcodes), alsways a label will come, no variables should be there after these two opcodes.
    c)I have asseumed that all the Symbols are pre-defined.Taking this assumption, there is no regarding Symbol used but not defined.
    d)While making symbol table in pass1, if any symbol is repeated it will repeat in symbol table too, with its respective address
    (showing where it is stored) and program counter also increments that time too, but while making the ObjectFile Only that address
    of the symbol will be used which was assigned to it first.
    e)The format has to be "LABEL OPCODE OPERAND" or "OPCODE OPERAND" , nothing can be left empty in both the formats,until the opcode
    used is CLA or STP.
    f)The labels are defined as ='value'.
