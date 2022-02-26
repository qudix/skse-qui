import os, argparse, zipfile

def make_zipfile(a_name):
    return zipfile.ZipFile(f"{a_name}.zip", "w", zipfile.ZIP_DEFLATED)

def make_rel_archive(a_args):
    zip = make_zipfile(a_args.name)
    def write(a_file, a_directory):
        name = os.path.basename(a_file)
        zip.write(a_file, f"{a_directory}/{name}")

    for file in a_args.plugin_files:
        write(file, "SKSE/Plugins")

    for file in a_args.swf_files:
        write(file, "Interface")

    for file in a_args.translation_files:
        write(file, "Interface/Translations")

def make_dbg_archive(a_args):
	zip = make_zipfile(f"{a_args.name}_pdb")
	for pdb in a_args.pdb_files:
		zip.write(pdb, os.path.basename(pdb))

def parse_arguments():
    parser = argparse.ArgumentParser(description="pack build artifacts for distribution")
    parser.add_argument("--name", type=str, help="archive name", required=True)
    parser.add_argument("--bin-dir", type=str, help="the project binary directory", required=True)
    parser.add_argument("--plugin-files", type=str, help="plugin files to pack", nargs="+", required=True)
    parser.add_argument("--pdb-files", type=str, help="pdb files to pack", nargs="+", required=True)
    parser.add_argument("--swf-files", type=str, help="swf files to pack", nargs="+")
    parser.add_argument("--translation-files", type=str, help="translation files to pack", nargs="+")
    return parser.parse_args()

def main():
    print("Packing artifacts...")

    args = parse_arguments()
    out = os.path.join(args.bin_dir, "build")
    os.makedirs(out, exist_ok=True)
    os.chdir(out)

    make_rel_archive(args)
    make_dbg_archive(args)

    print("Done.")

if __name__ == "__main__":
    main()
