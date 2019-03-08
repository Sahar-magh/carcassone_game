CLIENT_DIR=src/client
SERVER_DIR=src/serveur
INSTALL_DIR=install
TEST_DIR=src/test
UP_DIR=src/updateFunctions
STRUCT_DIR=src/structure

BIN=client1 client2 client3 server
TEST=test_client test_updateRoad test_updateCloister test_updateTown test_updateField

CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -g -O0
CSHARE=-fPIC -shared
LDFLAGS=`sdl-config --libs --cflags`

all: build

build: ${BIN}

test: ${TEST}
	@echo -e "\033[031m CLIENT TEST : \033[0m"	
	@./test_client
	@echo -e "\033[031m CLOISTER TEST : \033[0m"	
	@./test_updateCloister
	@echo -e "\033[031m ROAD TEST : \033[0m"
	@./test_updateRoad
	@echo -e "\033[031m TOWN TEST : \033[0m"
	@./test_updateTown
	@echo -e "\033[031m FIELD TEST : \033[0m"
	@./test_updateField

link.o: ${STRUCT_DIR}/link.c
	${CC} ${CFLAGS} -c ${STRUCT_DIR}/link.c

carte.o: ${STRUCT_DIR}/carte.c
	${CC} ${CFLAGS} -c ${STRUCT_DIR}/carte.c

test_carte.o: ${TEST_DIR}/test_carte.c
	${CC} ${CFLAGS} -c ${TEST_DIR}/test_carte.c

test_carte: test_carte.o carte.o link.o
	${CC} -o $@ test_carte.o carte.o link.o

test_client: test_client.o
	${CC} -o $@ test_client.o

test_client.o: ${TEST_DIR}/test_client.c
	${CC} ${CFLAGS} -I${TEST_DIR} ${TEST_DIR}/test_client.c -c 

test_updateRoad.o: ${TEST_DIR}/test_updateRoad.c
	${CC} ${CFLAGS} -c ${TEST_DIR}/test_updateRoad.c 

test_updateRoad: carte.o updateRoad.o link.o test_updateRoad.o
	${CC} -o $@ carte.o updateRoad.o link.o test_updateRoad.o

test_updateCloister.o: ${TEST_DIR}/test_updateCloister.c
	${CC} ${CFLAGS} -c ${TEST_DIR}/test_updateCloister.c

test_updateCloister: carte.o updateCloister.o link.o test_updateCloister.o
	${CC} -o $@ carte.o updateCloister.o link.o test_updateCloister.o

test_updateTown.o: ${TEST_DIR}/test_updateTown.c
	${CC} ${CFLAGS} -c ${TEST_DIR}/test_updateTown.c

test_updateTown: carte.o link.o updateTown.o test_updateTown.o Free.o
	${CC} -o $@ carte.o link.o updateTown.o test_updateTown.o Free.o

test_updateField.o: ${TEST_DIR}/test_updateField.c
	${CC} ${CFLAGS} -c ${TEST_DIR}/test_updateField.c

test_updateField: carte.o link.o updateField.o test_updateField.o updateTown.o Free.o
	${CC} -o $@ carte.o link.o updateField.o test_updateField.o updateTown.o Free.o

install: server client1 client2 client3 
	cp server ${INSTALL_DIR}/ && cp *.so ${INSTALL_DIR}/

clean:
	@rm -rf ${INSTALL_DIR}/server ${INSTALL_DIR}/*.so *.so *.o server *.out server test updateRoad updateTown test_updateRoad test_updateCloister test_updateTown *~ meeple updateField Free test_client test_updateField

client1: ${CLIENT_DIR}/client.c ${CLIENT_DIR}/carcassonne_interface.h ${STRUCT_DIR}/carte.c ${STRUCT_DIR}/link.c ${UP_DIR}/updateRoad.c ${STRUCT_DIR}/Free.c ${UP_DIR}/updateCloister.c ${UP_DIR}/updateTown.c
	${CC} ${CFLAGS} ${CSHARE} -o $@.so ${CLIENT_DIR}/client.c ${STRUCT_DIR}/carte.c ${STRUCT_DIR}/link.c ${UP_DIR}/updateRoad.c ${STRUCT_DIR}/Free.c ${UP_DIR}/updateCloister.c ${UP_DIR}/updateTown.c
client2: ${CLIENT_DIR}/client.c ${CLIENT_DIR}/carcassonne_interface.h ${STRUCT_DIR}/carte.c ${STRUCT_DIR}/link.c ${UP_DIR}/updateRoad.c ${STRUCT_DIR}/Free.c ${UP_DIR}/updateCloister.c ${UP_DIR}/updateTown.c
	${CC} ${CFLAGS} ${CSHARE} -o $@.so ${CLIENT_DIR}/client.c ${STRUCT_DIR}/carte.c ${STRUCT_DIR}/link.c ${UP_DIR}/updateRoad.c ${STRUCT_DIR}/Free.c ${UP_DIR}/updateCloister.c ${UP_DIR}/updateTown.c
client3: ${CLIENT_DIR}/client.c ${CLIENT_DIR}/carcassonne_interface.h ${STRUCT_DIR}/carte.c ${STRUCT_DIR}/link.c ${UP_DIR}/updateRoad.c ${STRUCT_DIR}/Free.c ${UP_DIR}/updateCloister.c ${UP_DIR}/updateTown.c
	${CC} ${CFLAGS} ${CSHARE} -o $@.so ${CLIENT_DIR}/client.c ${STRUCT_DIR}/carte.c ${STRUCT_DIR}/link.c ${UP_DIR}/updateRoad.c ${STRUCT_DIR}/Free.c ${UP_DIR}/updateCloister.c ${UP_DIR}/updateTown.c

serveur.o: ${SERVER_DIR}/serveur.c  ${SERVER_DIR}/carcassonne_interface.h 
	${CC} ${CFLAGS} -I${SERVER_DIR} ${SERVER_DIR}/serveur.c -c 

server: serveur.o carte.o link.o updateRoad.o updateCloister.o Free.o updateTown.o
	${CC} -o $@ serveur.o carte.o link.o updateRoad.o updateCloister.o Free.o updateTown.o -ldl
#${CC} -rdynamic -o $@ serveur.o carte.o link.o -ldl
aff:
	@echo
	@echo -e "\033[031mdossier racine : \033[0m" && ls -1 --color
	@echo
	@echo -e "\033[032mdossier client : \033[0m" && ls -1 --color ${CLIENT_DIR}
	@echo 
	@echo -e "\033[032mdossier serveur : \033[0m" && ls -1 --color ${SERVER_DIR}
	@echo
	@echo -e "\033[032mdossier install :\033[0m" && ls -1 --color ${INSTALL_DIR}
	@echo


test_aff.o: $(TEST_DIR)/test_aff.c test_aff.o
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test_aff.c -o test_aff.o

test_aff: test_aff.o
	$(CC) test_aff.o $(LDFLAGS) -o test_aff

exe: 
	./install/server ./install/*.so

test_link.o: $(TEST_DIR)/test_link.c
	${CC} ${CFLAGS} -c ${TEST_DIR}/test_link.c

test_link: test_link.o link.o carte.o
	$(CC) -o $@ test_link.o link.o carte.o

updateRoad.o: ${UP_DIR}/updateRoad.c
	$(CC) $(CFLAGS) -c ${UP_DIR}/updateRoad.c

updateCloister.o: ${UP_DIR}/updateCloister.c
	$(CC) $(CFLAGS) -c ${UP_DIR}/updateCloister.c

updateTown.o: ${UP_DIR}/updateTown.c
	$(CC) $(CFLAGS) -c ${UP_DIR}/updateTown.c

updateTown: updateTown.o carte.o link.o
	$(CC) -o $@ updateTown.o carte.o link.o

updateField.o: ${UP_DIR}/updateField.c
	$(CC) $(CFLAGS) -c ${UP_DIR}/updateField.c

updateField: updateField.o updateTown.o carte.o link.o
	$(CC) -o $@ updateTown.o carte.o link.o updateField.o

meeple.o: ${STRUCT_DIR}/meeple.c
	$(CC) $(CFLAGS) -c ${STRUCT_DIR}/meeple.c

meeple: meeple.o updateField.o updateTown.o updateRoad.o carte.o link.o
	$(CC) -o $@ meeple.o updateField.o updateTown.o updateRoad.o carte.o link.o

Free.o: ${STRUCT_DIR}/Free.c
	$(CC) $(CFLAGS) -c ${STRUCT_DIR}/Free.c

Free: Free.o link.o carte.o
	$(CC) -o $@ Free.o link.o carte.o
