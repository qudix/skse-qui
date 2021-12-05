import os

CXX_TYPES = (".c",".cpp",".cxx",".h",".hpp",".hxx")

def walk_dir(a_dir, types):
	temp = []
	for root, dirs, files in os.walk(a_dir):
		for file in files:
			if file.endswith(types):
				path = os.path.join(root, file)
				norm = os.path.normpath(path)
				slash = norm.replace("\\", "/")
				temp.append(slash)

	temp.sort()
	return temp

def make_cmake(a_dir):
	cxx = walk_dir(a_dir, CXX_TYPES)
	out = open(os.path.join("etc", "cmake", "source-list.cmake"), "w")
	out.write("set(CXX_FILES\n")
	for source in cxx:
		out.write(f"\t{source}\n")
	out.write(")\n")

def main():
	cur = os.path.dirname(os.path.realpath(__file__))
	os.chdir(cur + "/../..")
	make_cmake("src")

if __name__ == "__main__":
	main()