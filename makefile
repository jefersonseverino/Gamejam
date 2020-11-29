clientFile=main
clientName=CLIENT

all: compClient runClient

compClient:
	gcc -std=c17 -o $(clientName) $(clientFile).c -lallegro -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_dialog
runClient:
	./$(clientName)
