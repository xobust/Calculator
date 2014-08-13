Calculator
==========

Simple Calculator i made for a forum [chalange](http://www.sweclockers.com/forum/10-programmering-och-digitalt-skapande/1309649-progblemet-10-miniraknare/)


## Where is the source?
The folder still contains my vs project so the 
code is located in > Two stack algorithm > Two stack algorithm.cpp 


## How it works

It works like this:
* Convert the expression from [infix](http://en.wikipedia.org/wiki/Infix_notation) to [reverse polish](http://en.wikipedia.org/wiki/Reverse_Polish_notation) using dijkstras [shunting yard algorithm](http://en.wikipedia.org/wiki/Shunting-yard_algorithm)
* Output the reverse polis on a queue
* Calculate the reverse polish using the method below


```psudo


while output not empty

  if output.front is number
    numbers.push(number)
    
  if output.front is operator
    b = numbers.pop
    a = numbers.pop
    
    output.push( a operator b)

```

## The name

The name of the Project is Two stack algorithm because you need two stack to convert infix
to reverse polish. One for the operators and one for the numbers, but now i use a queue
asswel so the project sould be called two stacks and a queue algorithm


## Working with strings
Working with expression strings can be hard but i got a good string to double function
using string streams and i try to do bound checking all the time.

```c++
bool String2Double(const std::string& str, double& result) // bra string to nummer funktion från the interwebs
{
    std::istringstream ss(str);
    ss.imbue(std::locale::classic());
    ss >> result;
    return !ss.fail() && ss.eof();
}

```

## Complexity

The complexity sould be close to O(2N) 
