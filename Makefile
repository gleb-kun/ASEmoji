PREFIX ?= /usr/local
INCLUDE_DIR = $(PREFIX)/include/ASEmoji
LIB_DIR = $(PREFIX)/lib

SRC_DIR = sources
HEADERS = ASEmoji.h
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)
LIB_NAME = libASEmoji.a

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I.
AR = ar
ARFLAGS = rcs

all: $(LIB_NAME)
	@echo "Building $(LIB_NAME)"
	@if $(MAKE) $(LIB_NAME); then \
		echo "Build complete successfully"; \
	else \
		echo "Build failed"; exit 1; \
	fi

$(LIB_NAME): $(OBJS)
	@echo "Creating static library $(LIB_NAME)"
	@if $(AR) $(ARFLAGS) $@ $^; then \
		echo "Library $(LIB_NAME) created successfully"; \
	else \
		echo "Failed to create library $(LIB_NAME)"; exit 1; \
	fi

%.o: %.cpp $(HEADERS)
	@echo "Compiling $<"
	@if $(CXX) $(CXXFLAGS) -c $< -o $@; then \
		echo "Compiled $< successfully"; \
	else \
		echo "Compilation of $< failed"; exit 1; \
	fi

install: $(LIB_NAME)
	@echo "Installing $(LIB_NAME) to $(DESTDIR)$(LIB_DIR)"
	@if install -d $(DESTDIR)$(INCLUDE_DIR) && \
	   install -d $(DESTDIR)$(LIB_DIR) && \
	   install -m 644 $(HEADERS) $(DESTDIR)$(INCLUDE_DIR)/ && \
	   install -m 644 $(LIB_NAME) $(DESTDIR)$(LIB_DIR)/; then \
		echo "Installation complete"; \
	else \
		echo "Installation failed"; exit 1; \
	fi

uninstall:
	@echo "Uninstalling $(LIB_NAME)"
	@if rm -rf $(DESTDIR)$(INCLUDE_DIR) && rm -f $(DESTDIR)$(LIB_DIR)/$(LIB_NAME); then \
		echo "Uninstallation complete"; \
	else \
		echo "Uninstallation failed"; exit 1; \
	fi

clean:
	@echo "Cleaning up"
	@if rm -f $(OBJS) $(LIB_NAME); then \
		echo "Cleanup complete"; \
	else \
		echo "Cleanup failed"; exit 1; \
	fi

.PHONY: all install uninstall clean
