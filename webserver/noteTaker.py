import argparse
import browser

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='NoteTaker takes notes and stores bookmarks.')
    parser.add_argument("mode", help=
    """NoteTaker mode:
        start -- starts the server (necessary?)
        bookmark -- adds bookmark
        note -- adds new note
        edit -- edits or deletes current notes/bookmarks""")            
    args = parser.parse_args()


    
