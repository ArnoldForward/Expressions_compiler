# String_Calculator
You can enter any expression, for example: 57.16 + 2^3^1.5 - (365.78^sin(sqrt(5,243) + 11.78) + ctg(8.45+99)) / (5! + 8 - 11) and calculate it.

The calculator was wrote in pure C, with almost no use of standard language features. More precisely, only the pow () function was used from the standard library, because my implementation of this function is not yet accurate enough. The rest of the functions and algorithms are developed and written independently. All algorithms have either linear complexity (provided that the length of the number does not depend on the length of the expression), or logarithmic complexity (these are functions for calculating trigonometric functions). The calculator "understands" brackets, exponentiation, unary minus, factorial, exponential input, root extraction of any order, direct and inverse trigonometric functions (when implementing which the method of half division of the remainder was used, as in the binary search algorithm). Sequential exponentiation in the form 2^2^2^2 is understood right-associatively as 2^(2^(2^2)), i.e. 2^16. The program ignores spaces and catches input errors. As an argument to a trigonometric function, not only a real number can be passed, but also an expression of the form 3.147+5.56-1.45*7+55.8/7.1159, does not contain parentheses.

Test examples:

8.6871*0.5^(-0.189)*0.0237^ (-0.0147) + sqrt(5,12.69*8+32/0.897) + sin(98.7)

8.6871*0.5^(-0.189)*0.0237^ (-0.0147) + sqrt(5,12.69*8+32/0.897) + sin(98.7)+ ctg(sqrt(10,1024))

(sin(90) + sin(30) + cos(55.8) + 15.68)/12.35^(ctg(86.7)-sin(4.5))

(sin(90) + sin(30) + cos(55.8) + 15.68)/12.35^(ctg(86.7)  + sin(4.5))

((sin(90) + sin(30) + cos(55.8) + 15.68)/12.35^(ctg(86.7)-sin(4.5)))^(sin(90) * sin(30)^2) 

3.24e3 * 0.125^(-1.568)

348e-3 + 5*(sin(46.8 + 5125.67)/0.867 + 1.57)

-12.2257*1.25/0.88^5.556*1.125   +  45.248*0.987*1.789^5.457/0.897^0.55  -479.214*0.1297

(((sin(90) + sin(30) + cos(55.8) + 15.68)/12.35^(ctg(86.7)-sin(4.5)))^(sin(90) + sin(30) + 1))^(arcsin(0.5)^cos(60)^2)




