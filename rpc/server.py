from xmlrpc.server import SimpleXMLRPCServer 

def factorial(n):
    ans = 1
    for i in range(1,n+1):
        ans = ans * i 
    return ans
    
def square(n):
    answer = n * n
    return answer

server = SimpleXMLRPCServer(("localhost",8000),logRequests=False)
server.register_function(factorial,"rpc_factorial")
server.register_function(square,"rpc_square")

try:
    print("Listening on port 8000")
    server.serve_forever()

except:
    print("Exit")
