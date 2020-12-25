from distutils.core import setup, Extension

def main():
    setup(
            name="jsontophp",
            version="1.0.0",
            description="Python interface to convert JSON objects into PHP Objects"),
            author="Olivier Kessler",
            author_email="olivier.kessler@protonmail.com",
            ext_modules=[Extension("jsontophp", ["jsontophp.c"])])

if __name__ == "__main__":
    main()
            

