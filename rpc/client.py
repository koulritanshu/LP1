import xmlrpc.client

proxy = xmlrpc.client.ServerProxy("http://localhost:8000/")

while(True):
    print("1.FACTORIAL\n2.SQUARE\n3.EXIT")
    ch = int(input())
    if ch == 1:
        num = int(input())
        print(f"The factorial of {num} is {proxy.rpc_factorial(num)}")
    elif ch == 2:
        num = int(input())
        print(f"The square of {num} is {proxy.rpc_square(num)}")
    else:
        print("Bye")
        break