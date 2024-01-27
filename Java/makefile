JAR = snake.jar
JC = javac
MAIN = Game

#Class Files Directory
BINDIR = bin

JCFLAGS = -cp . -d $(BINDIR)

#Source Files
SRCS = $(wildcard *.java)

#Class Files
CLS = $(patsubst %.java, $(BINDIR)/%.class, $(SRCS))

default: jar
all: jar

$(CLS): $(BINDIR)/%.class: %.java
ifeq ($(OS),Windows_NT)
	@if not exist $(@D) @mkdir $(@D)
else
	@mkdir -p $(@D)
endif
	$(JC) $(JCFLAGS) $<
	
jar: $(CLS)
	jar cfe $(JAR) $(MAIN) -C $(BINDIR) .
	
clean:
	$(RM) -r $(BINDIR) $(JAR)
