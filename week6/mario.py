# TODO
def main():

    while True:
        n = int(input("type number between 1~8: "))
        if 1 <= n <= 8:
            break


    for i in range(1, n + 1):        
        for j in range(1, n + 1):    
            if j <= n - i:           
                print(" ", end="")
            else:
                print("#", end="")
        print(" ")  

main()
