#ifndef ERROR_H
# define ERROR_H

# define MALLOC_FAIL ": memory allocation failed."
# define FSTAT_FAILED ": fstat() failed."
# define MMAP_FAILED ": mmap() failed."
# define BAD_FILENAME ": No such file or directory."
# define BAD_ARCH ": The file was not recognized as a valid object file."
# define CLOSE_FAILED ": close() failed."
# define INVALID_OBJECT ": The file was not recognized as a valid object file."
# define NO_INPUT_OBJECT_FILE ": at least one file must be specified"

int		ft_error(char const *exec_name, char const *filename, char const *type);

#endif
