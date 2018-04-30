set nocompatible              " be iMproved, required
filetype off                  " required


" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

Plugin 'tpope/vim-fugitive'

Plugin 'Valloric/YouCompleteMe'

Plugin 'rdnetto/YCM-Generator'

Plugin 'vim-airline/vim-airline'

Plugin 'tpope/vim-surround'

Plugin 'tpope/vim-repeat'

Plugin 'vim-airline/vim-airline-themes'

Plugin 'scrooloose/nerdtree'

" All of your Plugins must be added before the following line
call vundle#end()            " required

filetype plugin indent on    " required

set t_Co=256

"set expandtab
set smarttab
set autoindent

syntax on
set tabstop=4
set shiftwidth=4
set softtabstop=0
set splitbelow
set splitright

set laststatus=2

autocmd StdinReadPre * let s:std_in=1
autocmd VimEnter * if argc() == 0 && !exists("s:std_in") | NERDTree | endif

