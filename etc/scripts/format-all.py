import os

FILE_TYPES = (".c",".cpp",".cxx",".h",".hpp",".hxx")

def format(a_dirs):
	files = list()
	for directory in a_dirs:
		for root, dirs, filenames in os.walk(directory):
			for filename in filenames:
				if filename.endswith(FILE_TYPES):
					files.append(root + '/' + filename)

	for file in files:
		os.system("clang-format.exe -i -style=file " + file)

def main():
	cur = os.path.dirname(os.path.realpath(__file__))
	os.chdir(cur + "/../..")
	format(["src"])

if __name__ == "__main__":
	main()
