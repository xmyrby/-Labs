import turtle
 
size = 300
n = 1
 
 
def koch_step(size, n):
    if n == 0:
        turtle.forward(size)
    else:
        koch_step(size / 3, n - 1)
        turtle.left(60)
        koch_step(size / 3, n - 1)
        turtle.right(120)
        koch_step(size / 3, n - 1)
        turtle.left(60)
        koch_step(size / 3, n - 1)
 
 
def draw(size, n):
    for i in range(3):
        koch_step(size, n)
        turtle.right(120)
 
 
draw(size, n)
