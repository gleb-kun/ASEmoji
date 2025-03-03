PREFIX ?= /usr/local
INCLUDE_DIR = $(PREFIX)/include/ASEmoji
LIB_DIR = $(PREFIX)/lib
CMAKE_DIR = $(PREFIX)/lib/cmake/ASEmoji

SRC_DIR = sources
HDR_DIR = headers

HEADERS = $(wildcard $(HDR_DIR)/*.h)
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(SRC_DIR)/%.o)
LIB_NAME = libASEmoji.a

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iheaders
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
	@$(AR) $(ARFLAGS) $@ $^

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@echo "Compiling $<"
	@if $(CXX) $(CXXFLAGS) -c $< -o $@; then \
		echo "Compiled $< successfully"; \
	else \
		echo "Compilation of $< failed"; exit 1; \
	fi

install: $(LIB_NAME)
	@echo "Installing $(LIB_NAME) to $(DESTDIR)$(LIB_DIR)"
	@echo "Creating directories..."
	@if install -d $(DESTDIR)$(INCLUDE_DIR); then \
		echo "Created $(DESTDIR)$(INCLUDE_DIR)"; \
	else \
		echo "Failed to create $(DESTDIR)$(INCLUDE_DIR)"; exit 1; \
	fi
	@if install -d $(DESTDIR)$(LIB_DIR); then \
		echo "Created $(DESTDIR)$(LIB_DIR)"; \
	else \
		echo "Failed to create $(DESTDIR)$(LIB_DIR)"; exit 1; \
	fi
	@if install -d $(DESTDIR)$(CMAKE_DIR); then \
		echo "Created $(DESTDIR)$(CMAKE_DIR)"; \
	else \
		echo "Failed to create $(DESTDIR)$(CMAKE_DIR)"; exit 1; \
	fi

	@echo "Installing header files..."
	@if install -m 644 $(HEADERS) $(DESTDIR)$(INCLUDE_DIR)/; then \
		echo "Header files installed successfully"; \
	else \
		echo "Failed to install header files"; exit 1; \
	fi

	@echo "Installing static library..."
	@if install -m 644 $(LIB_NAME) $(DESTDIR)$(LIB_DIR)/; then \
		echo "$(LIB_NAME) installed successfully"; \
	else \
		echo "Failed to install $(LIB_NAME)"; exit 1; \
	fi

	@echo "Installing CMake config files..."
	@if install -m 644 cmake/ASEmojiConfig.cmake $(DESTDIR)$(CMAKE_DIR)/; then \
		echo "ASEmojiConfig.cmake installed"; \
	else \
		echo "Failed to install ASEmojiConfig.cmake"; exit 1; \
	fi

	@if install -m 644 cmake/ASEmojiTargets.cmake $(DESTDIR)$(CMAKE_DIR)/; then \
		echo "ASEmojiTargets.cmake installed"; \
	else \
		echo "Failed to install ASEmojiTargets.cmake"; exit 1; \
	fi

uninstall:
	@echo "Uninstalling $(LIB_NAME)"
	@echo "Removing static library..."
	@if rm -f $(DESTDIR)$(LIB_DIR)/$(LIB_NAME); then \
		echo "$(LIB_NAME) removed successfully"; \
	else \
		echo "Failed to remove $(LIB_NAME)"; exit 1; \
	fi

	@echo "Removing header files directory..."
	@if rm -rf $(DESTDIR)$(INCLUDE_DIR); then \
		echo "$(DESTDIR)$(INCLUDE_DIR) removed successfully"; \
	else \
		echo "Failed to remove $(DESTDIR)$(INCLUDE_DIR)"; exit 1; \
	fi

	@echo "Removing CMake config directory..."
	@if rm -rf $(DESTDIR)$(CMAKE_DIR); then \
		echo "$(DESTDIR)$(CMAKE_DIR) removed successfully"; \
	else \
		echo "Failed to remove $(DESTDIR)$(CMAKE_DIR)"; exit 1; \
	fi

clean:
	@echo "Cleaning up"
	@if rm -f $(OBJS) $(LIB_NAME); then \
		echo "Cleanup complete"; \
	else \
		echo "Cleanup failed"; exit 1; \
	fi

.PHONY: all install uninstall clean
