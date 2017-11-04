# PDF Documentation

PDF Documentation based on the Official [PDF Specification](http://www.adobe.com/devnet/pdf/pdf_reference.html)


## WHITE-SPACE: "7.2.2"

```csv
 0 00 Null (NUL)
 9 09 HORIZONTAL TAB (HT)
10 0A LINE FEED (LF)
12 0C FORM FEED (FF)
13 0D CARRIAGE RETURN (CR)
32 20 SPACE (SP)
```

## DELIMETERS: "7.2.2" (page 12)

```csv
(  40 28  50 LEFT PARENTHESIS
)  41 29  51 RIGHT PARENTHESIS
<  60 3C  60 LESS-THAN SIGN
>  62 3E  62 GREATER-THAN SIGN
[  91 5B 133 LEFT SQUARE BRACKET
]  93 5D 135 RIGHT SQUARE BRACKET
{ 123 7B 173 LEFT CURLY BRACKET
} 125 7D 175 RIGHT CURLY BRACKET
/  47 2F  57 SOLIDUS
%  37 25  45 PERCENT SIGN
```

## "7.2.3 Comments"

Any occurrence of the PERCENT SIGN (25h) outside a string or stream introduces a comment.



## OBJECTS: "7.3 Objects" (page 13)

PDF includes eight basic types of objects: 

 * Boolean
 * Numeric (Integer/Real)
 * Strings
 * Names
 * Arrays
 * Dictionaries
   A dictionary shall be written as a sequence of key-value pairs enclosed in double angle brackets
   (<< >>)
 * Streams
   consists of a dictionary followed by zero or more bytes bracketed between the keywords
   stream and endstream
 * Null object

## 7.3.2 Boolean objects

 * true
