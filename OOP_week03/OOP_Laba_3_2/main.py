from roman import Roman

if __name__ == "__main__":
    num1 = Roman("X")
    num2 = Roman("V")

    print(f"{num1} + {num2} = {num1 + num2}")  # X + V = XV
    print(f"{num1} - {num2} = {num1 - num2}")  # X - V = V
    print(f"{num1} * {num2} = {num1 * num2}")  # X * V = L
    print(f"{num1} / {num2} = {num1 / num2}")  # X / V = II