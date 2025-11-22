import sys

def solve():
    # Step 1: Represent all characters and their patterns
    CHAR_MAP = {
        '0': " _ | ||_|", '1': "     |  |", '2': " _  _||_ ", '3': " _  _| _|",
        '4': "   |_|  |", '5': " _ |_  _|", '6': " _ |_ |_|", '7': " _   |  |",
        '8': " _ |_||_|", '9': " _ |_| _|", '+': "    | -+-", '-': "      ---",
        '*': "   \\ / / \\", '/': "     /  / ", '[': " _ |  |_ ", ']': " _   |_| "
    }
    PATTERN_MAP = {v: k for k, v in CHAR_MAP.items()}
    SYMBOLS = list(CHAR_MAP.keys())

    # Step 2: Pre-compute all possible 1-segment-flip transformations
    transitions = {char: [] for char in SYMBOLS}
    for i in range(len(SYMBOLS)):
        for j in range(i + 1, len(SYMBOLS)):
            char1, char2 = SYMBOLS[i], SYMBOLS[j]
            pattern1, pattern2 = CHAR_MAP[char1], CHAR_MAP[char2]
            
            diff = sum(1 for k in range(9) if pattern1[k] != pattern2[k])
            
            if diff == 1:
                transitions[char1].append(char2)
                transitions[char2].append(char1)

    # Step 3: Input Parsing
    n_str = sys.stdin.readline()
    if not n_str: return
    n = int(n_str)
    
    lines = [sys.stdin.readline().strip('\n') for _ in range(3)]
    precedence_str = sys.stdin.readline().strip()

    initial_equation = ""
    for i in range(n):
        pattern = lines[0][i*4:i*4+3] + lines[1][i*4:i*4+3] + lines[2][i*4:i*4+3]
        initial_equation += PATTERN_MAP.get(pattern, "?")

    # Step 4: Validate and Evaluate
    def evaluate(expression, precedence):
        try:
            def apply_op(op, b, a):
                if op == '+': return a + b
                if op == '-': return a - b
                if op == '*': return a * b
                if op == '/':
                    if b == 0: raise ZeroDivisionError
                    return a // b
            
            values, ops = [], []
            i = 0
            while i < len(expression):
                if expression[i].isdigit():
                    num = 0
                    while i < len(expression) and expression[i].isdigit():
                        num = num * 10 + int(expression[i])
                        i += 1
                    values.append(num)
                    continue
                elif expression[i] == '[':
                    ops.append(expression[i])
                elif expression[i] == ']':
                    while ops and ops[-1] != '[':
                        values.append(apply_op(ops.pop(), values.pop(), values.pop()))
                    if not ops or ops.pop() != '[': return None # Mismatched brackets
                    
                else: # Operator
                    while (ops and ops[-1] != '[' and 
                           precedence.get(ops[-1], 0) >= precedence.get(expression[i], 0)):
                        values.append(apply_op(ops.pop(), values.pop(), values.pop()))
                    ops.append(expression[i])
                i += 1

            while ops:
                values.append(apply_op(ops.pop(), values.pop(), values.pop()))

            return values[0] if len(values) == 1 else None # Invalid expression
        except (ZeroDivisionError, IndexError):
            return None

    def is_syntactically_valid(eq):
        balance = 0
        for i, char in enumerate(eq):
            if char == '[': balance += 1
            elif char == ']': balance -= 1
            if balance < 0: return False
            
            is_op = char in "+-*/"
            if is_op:
                if i == 0 or i == len(eq) - 1: return False
                if eq[i-1] in "+-*/[": return False
                if eq[i+1] in "+-*/]": return False
            if char == '0' and i + 1 < len(eq) and eq[i+1].isdigit():
                if i == 0 or not eq[i-1].isdigit(): return False # Invalid leading zero
        
        return balance == 0

    # Main logic
    precedence = {op: len(precedence_str) - i for i, op in enumerate(precedence_str)}
    total_worth = 0
    
    for i, char in enumerate(initial_equation):
        if char not in transitions: continue
        
        for new_char in transitions[char]:
            new_equation = list(initial_equation)
            new_equation[i] = new_char
            new_equation_str = "".join(new_equation)

            if is_syntactically_valid(new_equation_str):
                result = evaluate(new_equation_str, precedence)
                if result is not None and result >= 0:
                    total_worth += result

    # Step 5: Output
    print(total_worth)

solve()