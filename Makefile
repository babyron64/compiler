BIN = .
SRC = src
LIB = lib
TMP = tmp

CCPP = g++
ARGS = -I $(LIB) -L $(LIB) -std=c++11 -Wall

SA = stx_alz
SA_U = stx_util
LA = lex_alz
LA_U = lex_util
CMN = common

all: syntax lexer

clean:
	rm -f $(TMP)/* $(SA).exe

syntax: $(SRC)/syntax/$(SA).cpp $(SRC)/syntax/$(SA).hpp $(TMP)/$(SA_U).o $(BIN)/$(CMN).dll $(LIB)/$(CMN).hpp
	$(CCPP) $(ARGS) -o $(BIN)/$(SA).exe $(SRC)/syntax/$(SA).cpp $(TMP)/$(SA_U).o $(BIN)/$(CMN).dll

$(TMP)/$(SA_U).o: $(SRC)/syntax/$(SA_U).cpp $(SRC)/syntax/$(SA_U).hpp
	$(CCPP) $(ARGS) -c -o $(TMP)/$(SA_U).o $(SRC)/syntax/$(SA_U).cpp

lexer: $(SRC)/lexer/$(LA).cpp $(SRC)/lexer/$(LA).hpp $(TMP)/$(LA_U).o $(SRC)/lexer/$(LA_U).hpp $(BIN)/$(CMN).dll $(LIB)/$(CMN).hpp
	$(CCPP) $(ARGS) -o $(BIN)/$(LA).exe $(SRC)/lexer/$(LA).cpp $(TMP)/$(LA_U).o $(BIN)/$(CMN).dll

$(TMP)/$(LA_U).o: $(SRC)/lexer/$(LA_U).cpp $(SRC)/lexer/$(LA_U).hpp
	$(CCPP) $(ARGS) -c -o $(TMP)/$(LA_U).o $(SRC)/lexer/$(LA_U).cpp

$(TMP)/$(CMN).o: $(LIB)/$(CMN).cpp $(LIB)/$(CMN).hpp
	$(CCPP) $(ARGS) -c -o $(TMP)/$(CMN).o $(LIB)/$(CMN).cpp

$(BIN)/$(CMN).dll: $(TMP)/$(CMN).o
	$(CCPP) $(ARGS) -shared -o $(BIN)/$(CMN).dll $(TMP)/$(CMN).o