import argparse
import browser
import db
import sys

#Decision: full static
class Server:
    def __init__(self):
        self.qute = browser.Browser()
        self.mainPage = ''
        #TODO generate a basic page if it doesnt exist
        self.interface = {
                stop=self.stop, 
                bmark=self.addBookmark, 
                note=self.takeNote, 
                edit=self.edit}
    def start():
        '''show mainpage and eventloop'''
        qute.showPage(self.mainPage)
        self.eventLoop()

    def stop(self):
        sys.exit(0)

    def eventLoop(self):
        '''We listen for events and respond to them'''
        event = ''

        self.interface[event]



if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='NoteTaker takes notes and stores bookmarks.')
    parser.add_argument("mode", help=
    """NoteTaker mode:
        start -- starts the server (necessary?)
        bookmark -- adds bookmark
        note -- adds new note
        edit -- edits or deletes current notes/bookmarks""")            
    args = parser.parse_args()
    if mode == 'start':
        import noteServer #quiza lo defina en este modulo nomas
        noteServer.Server().start()
    if mode == 'bookmark':
    if mode == 'note':
    if mode == 'edit':
    if mode == 'stop':

    
