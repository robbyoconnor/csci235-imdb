CC=g++
FILES=Movie.cc Actor.cc main.cc

codons:	
	${CC} -g ${FILES} -o imdb
	./imdb 		
clean: 
	rm -rf imdb*	