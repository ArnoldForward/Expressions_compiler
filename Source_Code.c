#include <stdio.h>
#include <math.h>
#define MAX 500
#define NUM 100

double number(char line[])
{
    char base[MAX] = {0};
    char rise[NUM]  = {0};
    int len = 0;
    for(int i = 0; line[i] != '\0'; i++)
        len++;
    int point = 0, exp = 0;
    for(int i = 0; line[i] != '\0'; i++)
    {
        if(line[i] == 'e')
            exp = i;
        if(line[i] == '.')
            point = i;
    }
    int min_trig = 0;
    int j = 0;
    for(int i = 0; i < len; i++)
    {
        if(i == 0 && line[i] == '-')
            min_trig = 1;
        if(line[i] >= '0' && line[i] <= '9')
        {
            base[j] = line[i];
            j++;
        }
        if(exp != 0 && i == exp)
            break;
    }
    if(point != 0)
        point = j - point + min_trig;
    double number = 0;
    for(int i = 0; base[i] != '\0'; i++)
    {
        j--;
        number += (base[i] - 48) * pow(10, j);
    }
    number /= pow(10, point);
    if(min_trig == 1)
        number *= -1;
    min_trig = 0;
    int order = 0;
    int k = 0;
    if(exp != 0)
    {
        int z = 0;
        if(line[exp + 1] >= '0' && line[exp + 1] <= '9')
            z = exp + 1;
        else if(line[exp + 1] == '-')
        {
            min_trig = 1;
            z = exp + 2;
        }
        for(int i = z; line[i] != '\0'; i++)
        {
            rise[k] = line[i];
            k++;
        }
        for(int i = 0; rise[i] != '\0'; i++)
        {
            k--;
            order += (rise[i] - 48) * pow(10, k);
        }
        if(min_trig == 0)
            number *= pow(10, order);
        else if(min_trig == 1)
            number /= pow(10, order);
    }
    return number;
}

double exponents(char line[])
{
    int rise[10]  = {0};
    int j = 0;
    for(int i = 0; line[i] != '\0'; i++)
        if(line[i] == '^')
        {
            rise[j] = i;
            j++;
        }
    int len = 0;
    for(int i = 0; line[i] != '\0'; i++)
        len++;
    int count = 0;
    for(int i = 0; rise[i] != '\0'; i++)
        count++;
    count--;
    double base = 0;
    double exponent = 0;
    double result = 0;
    int counter = 0;
    char expo[100] = {0};
    j = 0;
    for(int i = rise[count] + 1; i < len; i++)
    {
        expo[j] = line[i];
        j++;
    }
    exponent = number(expo);
    while(counter < count)
    {
        j = 0;
        for(int i = 0; expo[i] != '\0'; i++)
            expo[i] = '\0';
        for(int i = rise[count - counter - 1] + 1; i < rise[count - counter]; i++)
        {
            expo[j] = line[i];
            j++;
        }
        base = number(expo);
        result = pow(base, exponent);
        exponent = result;
        counter++;
    }
    j = 0;
    for(int i = 0; expo[i] != '\0'; i++)
        expo[i] = '\0';
    for(int i = 0; i < rise[0]; i++)
    {
        expo[j] = line[i];
        j++;
    }
    base = number(expo);
    result = pow(base, exponent);
    return result;
}

double result(char line[])
{
    char curr_numb[NUM] = {0};
    double term = 0, num = 0, sum = 0;
    int j = 0;
    for(int i = 0; line[i] != '\0'; i++)
    {
        if(line[i] == '+')
            continue;
        if((line[i] >= '0' && line[i] <= '9') || line[i] == '.' || line[i] == 'e' || line[i] == '-' || line[i] == '^')
        {
            curr_numb[j] = line[i];
            j++;
        }
        if(line[i] == ',')
        {
            printf(" > Error! Use only point symbol '.' to divide fractional part of number from integer part\n");
            for(int k = 0; line[k] != '\0'; k++)
                line[k] = '\0';
            return 0;
        }
        if((line[i + 1] == '*' || line[i + 1] == '/' || line[i + 1] == '+' ||
            (line[i + 1] == '-' && line[i] != '^') || line[i + 1] == '\0') && line[i] >= '0' && line[i] <= '9')
        {
            int exp_trig = 0;
            for(int j = 0; curr_numb[j] != '\0'; j++)
                if(curr_numb[j] == '^')
                    exp_trig = 1;
            if(exp_trig == 1)
            {
                num = exponents(curr_numb);
                if(line[i - j + 1] == '-' && (line[i] - 48) % 2 == 0 && i > j)
                    num *= -1;
            }
            else if(exp_trig == 0)
                num = number(curr_numb);
            if(term == 0)
                term = num;
            else if(term != 0 && line[i - j] == '*')
                term *= num;
            else if(term != 0 && line[i - j - 1] == '*' && line[i - j] == '-')
                term *= num * (-1);
            else if(term != 0 && line[i - j] == '/')
                term /= num;
            else if(term != 0 && line[i - j - 1] == '/' && line[i - j] == '-')
                term /= num * (-1);
            if((line[i + 1] == '+' || line[i + 1] == '-' || line[i + 1] == '\0') && line[i] >= '0' && line[i] <= '9')
            {
                sum += term;
                term = 0;
            }
            for(int k = 0; curr_numb[k] != '\0'; k++)
                curr_numb[k] = '\0';
            j = 0;
        }
    }
    return sum;
}

void convert(double num, char final[])
{
    if(num == 0)
    {
        final[0] = '0';
        return ;
    }
    int minus = 0;
    if(num < 0)
    {
        num *= -1;
        minus = 1;
    }
    long int base = num;
    long int base_final = base;
    double frac = num - base;
    int k = 0;
    double div = 0.1;
    int counter = 0;
    while(k == 0)
    {
        k = frac / div;
        div /= 10;
        counter++;
    }
    counter--;
    char temp[MAX] = {0};
    int i = 0;
    while(base > 0)
    {
        temp[i] = base % 10 + 48;
        base /= 10;
        i++;
    }
    char base_part[MAX] = {0};
    int j = 0;
    if(minus == 1)
    {
        base_part[0] = '-';
        j++;
    }
    for(i -= 1; i >= 0; i--)
    {
        base_part[j] = temp[i];
        j++;
    }
    if(frac == 0)
    {
        j = 0;
        for(int i = 0; base_part[i] != '\0'; i++)
        {
            final[j] = base_part[i];
            j++;
        }
        return ;
    }
    char frac_rev[MAX] = {0};
    frac *= 1000000000;
    long int f = frac;
    if( f % 10 == 9)
        f += 1;
    int d = 0;
    while(f > 0)
    {
        d = f % 10;
        frac_rev[i] = d + 48;
        f /= 10;
        i++;
    }
    char frac_part[50] = {0};
    j = 0;
    while(j < counter)
    {
        frac_part[j] = '0';
        j++;
    }
    for(i -= 1; i >= 0; i--)
    {
        frac_part[j] = frac_rev[i];
        j++;
    }
    int fr_len = 0, fr_end = 0;
    for(int i = 0; frac_part[i] != '\0'; i++)
        fr_len++;
    for(int i = fr_len - 1; i >= 0; i--)
        if(frac_part[i] != '0')
        {
            fr_end = i;
            break;
        }
    for(int i = fr_end + 1; frac_part[i] != '\0'; i++)
        frac_part[i] = '\0';
    j = 0;
    if(base_final != 0)
    {
        for(int i = 0; base_part[i] != '\0'; i++)
        {
            final[j] = base_part[i];
            j++;
        }
    }
    else if(base_final == 0)
    {
        if(minus == 1)
        {
            final[j] = '-';
            j++;
        }
        final[j] = '0';
        j++;
    }
    if(frac != 0)
    {
        final[j] = '.';
        for(int i = 0; frac_part[i] != '\0'; i++)
        {
            j++;
            final[j] = frac_part[i];
        }
    }
    return ;
}

void parse_brackets(char line[])
{
    char input [MAX] = {0};
    int brac_count = 0;
    for(int i = 0; line[i] != '\0'; i++)
        if(line[i] == '(')
            brac_count++;
    if(brac_count == 0)
    {
        convert(result(line), input);
        printf(" > ");
        puts(input);
        return;
    }
    while(brac_count > 0)
    {
        char brackets  [50]  = {0};
        int numbers    [50]  = {0};
        char nested    [MAX] = {0};
        int brac = 0, nums = 0;
        for(int i = 0; line[i] != '\0'; i++)
        {
            if(line[i] == '(' || line[i] == ')')
            {
                brackets[brac] = line[i];
                brac++;
                numbers[nums] = i;
                nums++;
            }
        }
        int k = 0;
        int open = 0, close = 0;
        for(int i = 0; brackets[i] != '\0'; i++)
        {
            if(brackets[i] == '(' && brackets[i + 1] == '(')
                continue;
            if(brackets[i] == '(' && brackets[i + 1] == ')')
            {
                open = numbers[i];
                close = numbers[i + 1];
                for(int j = numbers[i] + 1; j < numbers[i + 1]; j++)
                {
                    nested[k] = line[j];
                    k++;
                    line[j] = 'z';
                }
            }
            break;
        }
        convert(result(nested), input);
        int counter = 0;
        for(int i = 0; input[i] != '\0'; i++)
            counter++;
        k = 0;
        for(int i = 0; line[i] != '\0'; i++)
        {
            if(line[i] == 'z' && k < counter)
            {
                line[i] = input[k];
                k++;
            }
            if(k >= counter && line[i] == 'z')
                continue;
        }
        char line_next[MAX] = {0};
        k = 0;
        for(int i = 0; line[i] != '\0'; i++)
            if(line[i] != 'z' && i != open && i != close)
            {
                line_next[k] = line[i];
                k++;
            }
        for(int i = 0; input[i] != '\0'; i++)
            input[i] = '\0';
        convert(result(line_next), input);
        for(int i = 0; line[i] != '\0'; i++)
            line[i] = '\0';
        int j = 0;
        for(int i = 0; line_next[i] != '\0'; i++)
        {
            line[j] = line_next[i];
            j++;
        }
        brac_count--;
    }
    printf(" > ");
    puts(input);
}

void parse_input(char line[])
{
    char temp[200] = {0};
    int j = 0;
    for(int i = 0; line[i] != '\0'; i++)
        if((line[i] == '+' && line[i + 1] == '-') || (line[i] == '-' && line[i + 1] == '-'))
            line[i] = ' ';
    for(int i = 0; line[i] != '\0'; i++)
    {
        if( line[i] == 'w' || line[i] == ';' || line[i] == 'y' || line[i] == 'u' || line[i] == '?' ||
            line[i] == 'p' || line[i] == 'd' || line[i] == 'f' || line[i] == 'h' || line[i] == '`' ||
            line[i] == 'j' || line[i] == 'k' || line[i] == 'l' || line[i] == ':' || line[i] == 'z' ||
            line[i] == 'x' || line[i] == 'v' || line[i] == 'b' || line[i] == 'm' || line[i] == '@' ||
            line[i] == '#' || line[i] == '$' || line[i] == '%' || line[i] == '&' || line[i] == '~' ||
            line[i] == '<' || line[i] == '>' || (line[i] >= 'A' && line[i] <= 'Z'))
        {
            printf(" > Error. Wrong symbol! Please, try again\n");
            return ;
        }
        if(line[i] == '[' || line[i] == ']' || line[i] == '{' || line[i] == '}')
        {
            printf(" > Error. Wrong brackets! Use only round brackets '(' and ')'");
            return;
        }
        if((line[i] == 's' && !(line[i + 1] == 'i' && line[i + 2] == 'n')) &&
           (line[i] == 's' && !(line[i + 1] == 'q' && line[i + 2] == 'r' && line[i + 3] == 't')) &&
           (line[i] == 's' && !(line[i - 1] == 'o' && line[i - 2] == 'c')))
        {
            printf(" > Error(1). Unknown option of wrong command. Try again, please\n");
            return;
        }
        if((line[i] == 'c' && !(line[i + 1] == 'o' && line[i + 2] == 's')) &&
           (line[i] == 'c' && !(line[i + 1] == 't' && line[i + 2] == 'g')))
        {
            printf(" > Error(2). Unknown option of wrong command. Try again, please\n");
            return;
        }
        if((line[i] == 't' && !(line[i + 1] == 'a' && line[i + 2] == 'n')) &&
           (line[i] == 't' && !(line[i - 1] == 'c' && line[i + 1] == 'g')) &&
           (line[i] == 't' && !(line[i - 1] == 'r' && line[i - 2] == 'q' && line[i - 3] == 's')))
        {
            printf(" > Error(3). Unknown option of wrong command. Try again, please\n");
            return;
        }
        if(line[i] == 'i' && !(line[i + 1] == 'n' && line[i - 1] == 's'))
        {
            printf(" > Error(4). Unknown option of wrong command. Try again, please\n");
            return;
        }
        if((line[i] == 'n' && !(line[i - 1] == 'i' && line[i - 2] == 's')) &&
           (line[i] == 'n' && !(line[i - 1] == 'a' && line[i - 2] == 't')))
        {
            printf(" > Error(5). Unknown option of wrong command. Try again, please\n");
            return;
        }
        if(line[i] == 'a' && !(line[i - 1] == 't' && line[i + 1] == 'n'))
        {
            printf(" > Error(6). Unknown option of wrong command. Try again, please\n");
            return;
        }
        if(line[i] == 'g' && !(line[i - 1] == 't' && line[i - 2] == 'c'))
        {
            printf(" > Error(7). Unknown option of wrong command. Try again, please\n");
            return;
        }
        if(line[i] == 'q' && !(line[i - 1] == 's' && line[i + 1] == 'r' && line[i + 2] == 't'))
        {
            printf(" > Error(8). Unknown option of wrong command. Try again, please\n");
            return;
        }
        if(line[i] == 'r' && !(line[i + 1] == 't' && line[i - 1] == 'q' && line[i - 2] == 's'))
        {
            printf(" > Error(9). Unknown option of wrong command. Try again, please\n");
            return;
        }
        if(((line[i] == 'n' && line[i - 1] == 'i') || (line[i] == 's' && line[i - 1] == 'o') ||
            (line[i] == 'n' && line[i - 1] == 'a') || (line[i] == 'g' && line[i - 1] == 't') ||
            (line[i] == 't' && line[i] == 'r')) && line[i + 1] != '(')
        {
            printf(" > Error(10). Unknown option of wrong command. Try again, please\n");
            return;
        }
        if(((line[i] >= '0' && line[i] <= '9') || line[i] == ')') && line[i + 1] == '(')
        {
            printf(" > Error! Missing sign before bracket! Try again, please\n");
            return;
        }
        if(line[i] == ')' && (line[i + 1] == '(' || (line[i + 1] >= '0' && line[i + 1] <= '9')))
        {
            printf(" > Error! Missing sign after bracket! Try again, please\n");
            return;
        }
        if(line[i] != ' ')
        {
            temp[j] = line[i];
            j++;
        }
    }
    int brackets = 0;
    for(int i = 0; temp[i] != '\0'; i++)
    {
        if(temp[i] == '(')
            brackets++;
        if(temp[i] == ')')
            brackets--;
        if(brackets < 0)
            break;
    }
    if(brackets != 0)
    {
        printf(" > Error! Wrong brackets combination!\n");
        return;
    }
    for(int i = 0; line[i] != '\0'; i++)
        line[i] = '\0';
    j = 0;
    for(int i = 0; temp[i] != '\0'; i++)
    {
        line[j] = temp[i];
        j++;
    }
}

void ignore_spaces(char line[])
{
    char temp[MAX] = {0};
    int j = 0;
    for(int i = 0; line[i] != '\0'; i++)
        if((line[i] == '+' && line[i + 1] == '-') || (line[i] == '-' && line[i + 1] == '-'))
            line[i] = ' ';
    for(int i = 0; line[i] != '\0'; i++)
        if(line[i] != ' ')
        {
            temp[j] = line[i];
            j++;
        }
    for(int i = 0; line[i] != '\0'; i++)
        line[i] = '\0';
    j = 0;
    for(int i = 0; temp[i] != '\0'; i++)
    {
        line[j] = temp[i];
        j++;
    }
}

double root(int root, double num)
{
    int minus = 0;
    if(num < 0)
    {
        minus = 1;
        num *= -1;
    }
    int base_int = 0; double num_find = 0; int temp = 0;
    while(num_find <= num)
    {
        base_int++;
        temp = base_int;
        int z = temp;
        for(int i = 0; i < root - 1; i++)
        {
            temp *= z;
        }
        num_find = temp;
    }
    double start = base_int - 1;
    int exper = start;
    int z = exper;
    for(int i = 0; i < root - 1; i++)
        exper *= z;
    if(root % 2 == 0 && exper < 0)
        exper *= -1;
    if(exper == num)
        return z;
    double mid = 0.5;
    double base = start + mid;
    int counter = 0;
    double temp1 = base;
    while(num_find - num >= 0.00000001 || num_find - num <= -0.00000001)
    {
        base = temp1;
        for(int i = 0; i < root - 1; i++)
            base *= temp1;
        num_find = base;
        if(num_find > num)
            temp1 -= mid / 2;
        else if(num_find < num)
            temp1 += mid / 2;
        mid /= 2;
        counter++;
    }
    base = temp1;
    if(minus == 1 && root % 2 == 0)
    {
        printf("Wrong expression!\n");
        return 0;
    }
    else if(minus == 1 && root % 2 != 0)
        base *= -1;
    return base;
}

void sqr(char line[])
{
    int j = 0;
    char sqrt[50]  = {0};
    int sqrt_trig = 0, beg = 0, len = 0;
    for(int i = 0; line[i] != '\0'; i++)
    {
        if(line[i] == 's' && line[i + 1] == 'q' && line[i + 2] == 'r' && line[i + 3] == 't')
        {
            sqrt_trig = 1;
            beg = i;
        }
        if(sqrt_trig == 1)
        {
            sqrt[j] = line[i];
            j++;
        }
        if(sqrt_trig == 1 && line[i] == ')')
            break;
    }
    for(int i = 0; sqrt[i] != '\0'; i++)
        len++;
    j = 0;
    for(int i = 0; sqrt[i] != '\0'; i++)
        if(sqrt[i] >= '0' && sqrt[i] <= '9')
        {
            j++;
            if(sqrt[i + 1] == ',')
                break;
        }
    int first = 0;
    for(int i = 0; sqrt[i] != '\0'; i++)
        if(sqrt[i] >= '0' && sqrt[i] <= '9')
        {
            j--;
            first += (sqrt[i] - 48) * pow(10, j);
            if(sqrt[i + 1] == ',')
                break;
        }
    j = 0;
    int start = 0, minus = 0;
    for(int i = 0; sqrt[i] != '\0'; i++)
    {
        if(sqrt[i - 1] == ',' && sqrt[i] != '-')
            start = i;
        else if(sqrt[i - 1] == ',' && sqrt[i] == '-')
        {
            start = i + 1;
            minus = 1;
        }
        if(start != 0 && sqrt[i] >= '0' && sqrt[i] <= '9')
        {
            j++;
            if(sqrt[i + 1] == ')')
                break;
        }
    }
    double second = 0;
    char sec[100] = {0};
    j = 0;
    for(int i = start; sqrt[i] != '\0'; i++)
    {
        sec[j] = sqrt[i];
        j++;
        if(sqrt[i + 1] == ')')
            break;
    }
    second = result(sec);
    for(int i = beg; i < beg + len; i++)
        line[i] = 'z';
    for(int i = 0; sqrt[i] != '\0'; i++)
        sqrt[i] = '\0';
    double res = root(first, second);
    if(minus == 1)
        res *= -1;
    convert(res, sqrt);
    j = beg;
    for(int i = 0; sqrt[i] != '\0'; i++)
    {
        line[j] = sqrt[i];
        j++;
    }
    char temp[200] = {0};
    j = 0;
    for(int i = 0; line[i] != '\0'; i++)
        if(line[i] != 'z')
        {
            temp[j] = line[i];
            j++;
        }
    for(int i = 0; line[i] != '\0'; i++)
        line[i] = '\0';
    j = 0;
    for(int i = 0; temp[i] != '\0'; i++)
    {
        line[j] = temp[i];
        j++;
    }
}

void parse_sqrts(char line[])
{
    while(1)
    {
        int sqr_trig = 0;
        for(int i = 0; line[i] != '\0'; i++)
            if(line[i] == 's' && line[i + 1] == 'q' && line[i + 2] == 'r' && line[i + 3] == 't')
            {
                sqr_trig = 1;
                break;
            }
        if(sqr_trig == 1)
            sqr(line);
        else if(sqr_trig == 0)
            break;
    }
}

double sin(double grad)
{
    if(grad > 360)
    {
        int mult = grad / 360;
        int base = mult * 360;
        grad -= base;
    }
    if(grad > 90 && grad <= 180)
        grad = 180 - grad;
    else if(grad > 180 && grad <= 270)
    {
        grad -= 180;
        grad *= -1;
    }
    else if(grad > 270 && grad <= 360)
        grad = 180 - grad;
    double rad = 0;
    rad = grad * 3.14159/180;
    rad = rad - pow(rad, 3)/6 + pow(rad, 5)/120 - pow(rad, 7)/5040 +
    pow(rad, 9)/362880 - pow(rad, 11)/39916800 + pow(rad, 13)/6227020800 - pow(rad, 15)/1307674368000;
    return rad;
}

double cos(double grad)
{
    if(grad > 360)
    {
        int mult = grad / 360;
        int base = mult * 360;
        grad -= base;
    }
    double rad = 0;

    if(grad > 90 && grad <= 270)
    {
        grad -= 180;
        rad = grad * 3.14159/180;
        rad = 1 - pow(rad, 2)/2 + pow(rad, 4)/24 - pow(rad, 6)/720 +
        pow(rad, 8)/40320 - pow(rad, 10)/3628800 + pow(rad, 12)/479001600 - pow(rad, 14)/87178291200;
        rad *= -1;
        return rad;
    }
    else if(grad > 270 && grad <= 360)
        grad -= 360;
    rad = grad * 3.14159/180;
    rad = 1 - pow(rad, 2)/2 + pow(rad, 4)/24 - pow(rad, 6)/720 +
    pow(rad, 8)/40320 - pow(rad, 10)/3628800 + pow(rad, 12)/479001600 - pow(rad, 14)/87178291200;
    return rad;
}

void trigon(char line[])
{
    int len = 0;
    for(int i = 0; line[i] != '\0'; i++)
        len++;
    char trigon[50] = {0};
    int sin_trig = 0, cos_trig = 0, tan_trig = 0, ctg_trig = 0;
    int j = 0;
    int start = 0, end = 0;
    for(int i = 0; line[i] != '\0'; i++)
    {
        if(line[i] == 's' && line[i + 1] == 'i' && line[i + 2] == 'n')
        {
            sin_trig = 1;
            start = i;
        }
        if(sin_trig == 1 && ((line[i] >= '0' && line[i] <= '9') || line[i] == '-' || line[i] == '.' || line[i] == '+' ||
                         line[i] == '*' || line[i] == '/' || line[i] == '^' || line[i] == ',' || line[i] == 'e'))
        {
            trigon[j] = line[i];
            j++;
        }
        if(line[i] == ')' && sin_trig == 1)
        {
            end = i;
            break;
        }
        if(line[i] == 'c' && line[i + 1] == 'o' && line[i + 2] == 's')
        {
            cos_trig = 1;
            start = i;
        }
        if(cos_trig == 1 && ((line[i] >= '0' && line[i] <= '9') || line[i] == '-' || line[i] == '.' || line[i] == '+' ||
                         line[i] == '*' || line[i] == '/' || line[i] == '^' || line[i] == ',' || line[i] == 'e'))
        {
            trigon[j] = line[i];
            j++;
        }
        if(line[i] == ')' && cos_trig == 1)
        {
            end = i;
            break;
        }
        if(line[i] == 't' && line[i + 1] == 'a' && line[i + 2] == 'n')
        {
            tan_trig = 1;
            start = i;
        }
        if(tan_trig == 1 && ((line[i] >= '0' && line[i] <= '9') || line[i] == '-' || line[i] == '.' || line[i] == '+' ||
                         line[i] == '*' || line[i] == '/' || line[i] == '^' || line[i] == ',' || line[i] == 'e'))
        {
            trigon[j] = line[i];
            j++;
        }
        if(line[i] == ')' && tan_trig == 1)
        {
            end = i;
            break;
        }
        if(line[i] == 'c' && line[i + 1] == 't' && line[i + 2] == 'g')
        {
            ctg_trig = 1;
            start = i;
        }
        if(ctg_trig == 1 && ((line[i] >= '0' && line[i] <= '9') || line[i] == '-' || line[i] == '.' || line[i] == '+' ||
                         line[i] == '*' || line[i] == '/' || line[i] == '^' || line[i] == ',' || line[i] == 'e'))
        {
            trigon[j] = line[i];
            j++;
        }
        if(line[i] == ')' && ctg_trig == 1)
        {
            end = i;
            break;
        }
    }
    for(int i = start; i <= end; i++)
        line[i] = 'z';
    double x = 0;
    double tem = result(trigon);
    int sign = 1;
    if(tem < 0)
    {
        tem *= -1;
        sign = -1;
    }
    if(sin_trig == 1)
    {
        int t = tem;
        if(t % 90 == 0 && t % 180 != 0)
        {
            x = 1;
            if((t / 180) % 2 != 0 && sign == 1)
                x = -1;
            if((t / 180) % 2 != 0 && sign == -1)
                x = 1;
            if((t / 180) % 2 == 0 && sign == -1)
                x = -1;
        }
        else if((t % 30 == 0 || t % 150 == 0) && (t % 60 != 0 && t % 90 != 0 && t % 120 != 0 && t % 180 != 0))
        {
            x = 0.5;
            if((t / 180) % 2 != 0 && sign == 1)
                x = -0.5;
            if((t / 180) % 2 != 0 && sign == -1)
                x = 0.5;
            if((t / 180) % 2 == 0 && sign == -1)
                x = -0.5;
        }
        else
            x = sin(tem) * sign;
    }
    else if(cos_trig == 1)
    {
        int t = tem;
        if(t % 90 == 0 && t % 180 != 0)
            x = 0;
        else
            x = cos(tem);
    }
    else if(tan_trig == 1)
        x = sin(result(trigon)) / cos(result(trigon));
    else if(ctg_trig == 1)
        x = cos(result(trigon)) / sin(result(trigon));
    for(int i = 0; trigon[i] != '\0'; i++)
        trigon[i] = '\0';
    convert(x, trigon);
    j = 0;
    for(int i = start; i <= end; i++)
    {
        line[i] = trigon[j];
        j++;
    }
    char temp[200] = {0};
    j = 0;
    for(int i = 0; i < start; i++)
    {
        temp[j] = line[i];
        j++;
    }
    for(int i = 0; trigon[i] != '\0'; i++)
    {
        temp[j] = trigon[i];
        j++;
    }
    for(int i = end + 1; line[i] != '\0'; i++)
    {
        temp[j] = line[i];
        j++;
    }
    for(int i = 0; i < len; i++)
        line[i] = '\0';
    j = 0;
    for(int i = 0; temp[i] != '\0'; i++)
    {
        line[j] = temp[i];
        j++;
    }
}

void parse_trigon(char line[])
{
    while(1)
    {
        int trigon_trig = 0;
        for(int i = 0; line[i] != '\0'; i++)
            if((line[i] == 's' && line[i + 1] == 'i' && line[i + 2] == 'n') ||
               (line[i] == 'c' && line[i + 1] == 'o' && line[i + 2] == 's') ||
               (line[i] == 't' && line[i + 1] == 'a' && line[i + 2] == 'n') ||
               (line[i] == 'c' && line[i + 1] == 't' && line[i + 2] == 'g'))
            {
                trigon_trig = 1;
                break;
            }
        if(trigon_trig == 1)
            trigon(line);
        else if(trigon_trig == 0)
            break;
    }
}

void factorial(char line[])
{
    int start = 0, end = 0;
    for(int i = 0; line[i] != '\0'; i++)
        if(line[i] == '!')
            end = i;
    for(int i = end - 1; i >= 0; i--)
    {
        if(line[i] == '.')
        {
            printf(" > Error! Factorial may be only positive integer. Try again, please\n");
            break;
        }
        if((line[i] < '0' || line[i] > '9') && line[i] != '.')
        {
            start = i;
            break;
        }
    }
    char factor[NUM] = {0};
    int j = 0;
    if(start == 0)
        start = -1;
    for(int i = start + 1; i < end; i++)
    {
        factor[j] = line[i];
        j++;
    }
    long long int num = 0;
    int len = j;
    for(int i = 0; i < len; i++)
    {
        j--;
        num += (factor[i] - 48) * pow(10, j);
    }
    long long int factorial = 1;
    for(int i = 1; i <= num; i++)
        factorial *= i;
    for(int i = 0; factor[i] != '\0'; i++)
        factor[i] = '\0';
    convert(factorial, factor);
    char temp[MAX] = {0};
    j = 0;
    for(int i = 0; i <= start; i++)
    {
        temp[j] = line[i];
        j++;
    }
    for(int i = 0; factor[i] != '\0'; i++)
    {
        temp[j] = factor[i];
        j++;
    }
    for(int i = end + 1; line[i] != '\0'; i++)
    {
        temp[j] = line[i];
        j++;
    }
    for(int i = 0; line[i] != '\0'; i++)
        line[i] = '\0';
    j = 0;
    for(int i = 0; temp[i] != '\0'; i++)
    {
        line[j] = temp[i];
        j++;
    }
}

void parse_factorials(char line[])
{
    while(1)
    {
        int trigger = 0;
        for(int i = 0; line[i] != '\0'; i++)
            if(line[i] == '!')
            {
                trigger = 1;
                break;
            }
        if(trigger == 1)
            factorial(line);
        if(trigger == 0)
            break;
    }
}

void start(char line[])
{
    printf("\n ***********************************************| STRING CALCULATOR |*************************************************\n");
    printf(" *********|                                                                                                |**********\n");
    printf(" *********|          Enter string expression. You can use digits from '0' to '9', and symbols: '.', '+',   |**********\n");
    printf(" *********|   '-', '*', '/', '(', ')'. Also you can use an exponential input, in form '57e3' (understands  |**********\n");
    printf(" *********|   as 57000) or '28e-4' (understands as 0.028),  '^'  for exponentation  (in form of 7.8^5.1)   |**********\n");
    printf(" *********|   root extraction  of  any integer  degree, in  form 'sqrt(7, 4892.17)',  where   the  first   |**********\n");
    printf(" *********|   number is  integer degree, input trigonometric  functions,  in form 'sin(7.46)', cos(254),   |**********\n");
    printf(" *********|   'tan(185) of 'ctg(12.5)', and factorial of positive integer number in form '5!' (what means  |**********\n");
    printf(" *********|    '5*4*3*2*1' and gives '120'. Program  catches incorrect input and ignores  spaces.  Go!     |**********\n");
    printf(" *********|                                                                                                |**********\n");
    printf(" ---------------------------------------------------------------------------------------------------------------------\n\n");
    while(1)
    {
        printf(" > ");
        gets(line);
        parse_input(line);
        parse_factorials(line);
        parse_sqrts(line);
        parse_trigon(line);
        ignore_spaces(line);
        parse_brackets(line);
        for(int i = 0; line[i] != '\0'; i++)
            line[i] = '\0';
    }
}

int main()
{
    char expression[MAX] = {0};
    start(expression);
    return 0;
}
