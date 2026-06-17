print("If you want to exit enter q, reset enter r")

calc = ""
tokens = []

while True:
    number = input("Number:")
    expression = input("Expression:")
    digit = False
    if number != "q" and number != "r":
        try:
            num = float(number)
            digit = True
        except:
            print("Invalid number")
            continue

    if number == "q" or expression == "q":
        break

    elif number == "r" or expression == "r":
        calc = ""
        continue
        
    elif digit and expression in ["=", "+", "-", "*", "/"]:

        calc += number + " "
        tokens.append(float(number))
        tokens.append(expression)

        if expression != "=":
            calc += expression + " "
        else:
            print("eval:", eval(calc))

            parts = calc.split()

            idx = 0
            while idx < len(parts):
                if parts[idx] in ["*", "/"]:
                    num1 = float(parts[idx - 1])
                    op = parts[idx]
                    num2 = float(parts[idx + 1])
                    
                    if op == "*":
                        res = num1 * num2
                    elif op == "/":
                        res = num1 / num2
                        
                    parts[idx - 1 : idx + 2] = [str(res)]
                    idx -= 1
                else:
                    idx += 1

            total = float(parts[0])
            
            i = 1
            while i < len(parts):
                op = parts[i]
                num = float(parts[i+1])

                if op == "+":
                    total += num
                elif op == "-":
                    total -= num
                
                i += 2 

            print("manual:", str(total))

            calc = ""
    else:
        print("Make sure that you entered a valid number, and a valid operator (Not two or more as well)")