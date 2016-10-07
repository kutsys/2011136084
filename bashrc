# ~/.bashrc: 로그인하지 않은 쉘들을 위해 bash(1)에 의해 실행된다.
# /usr/share/doc/bash/examples/startup-files 을 보아라 (bash-doc 패키지 안의)
# 예를 들어,

# 상호적으로 실행되지 않으면 아무것도 하지 않는다.
case $- in
    *i*) ;;
      *) return;;
esac

# (명령어)히스토리에 중복된 라인 혹은 공백으로 시작하는 라인을 넣지 마라.
# 더 많은 옵션을 대해 bash(1)을 보아라.
HISTCONTROL=ignoreboth
# HISTCONTROL은 중복되어지는 명령에 대한 기록 유무를 지정하는 변수이다.

# 히스토리 파일에 추가할 때, 덮어씌우지 마라.(덮어써서 저장하지 마라)
shopt -s histappend
# shopt 는 shell option의 약자로, 이것을 이용해 여러 shell의 옵션을 조회 및 지정할 수 있다.
# -s optname은 optname을 활성화(설정)한다는 의미이다.

# 히스토리 길이 설정을 위해 bash(1)의 HISTSIZE 와 HISTFILESIZE를 보아라
HISTSIZE=1000
HISTFILESIZE=2000
# 변수 값 대입

# 각 명령 후에 창 크기를 확인하고 필요하다면 LINES와 COLUMS 값을 갱신한다
shopt -s checkwinsize
# 해당 checkwinsize 옵션을 활성화하는 명령이다.

# 설정했다면, 경로명 확장 문맥에서 사용되는 "**" 패턴은 모든 파일과 0개 혹은 더 많은 디렉토리와 서브디렉토리들에 대응될 것이다.
#shopt -s globstar


# 텍스트가 아닌 입력 파일들에 대해 less를 더 좋게 만든다. lesspipe(1)을 보아라.
[ -x /usr/bin/lesspipe ] && eval "$(SHELL=/bin/sh lesspipe)"

# chroot를 식별하기 위한 변수를 설정한다.(당신이 일하는 프롬프트 밑에서 사용되는)
if [ -z "${debian_chroot:-}" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

# 원하는 프롬프트를 설정한다.(설정하지 않는다면 색상이 없다)
case "$TERM" in
    xterm-color|*-256color) color_prompt=yes;;
esac

# 색상이 입혀진 프롬프트를 위한 주석, 터미널의 성능에 된다면;
# 유저를 혼랍스럽지 않게 하기 위해 기본적으로 색상 기능은 꺼져 있다.
# 터미널 창의 중점은 프롬프트가 아니라 명령의 출력이다.
#force_color_prompt=yes

if [ -n "$force_color_prompt" ]; then
    if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
	# 우리는 Ecma-48에 따르는 색상 지원을 가진다.(ISO/IEC-6429)
	# (대부분 이것을 지원하고 매우 가끔 지원하지 않는 경우 staf보다 stf를 지원합니다.)
	color_prompt=yes
    else
	color_prompt=
    fi
fi

if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
unset color_prompt force_color_prompt

# xterm일 경우 타이틀을 user@host:dir로 설정한다.
case "$TERM" in
xterm*|rxvt*)
    PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
    ;;
*)
    ;;
esac

# ls의 색상 지원을 활성화하고 유용한 alias들을 추가한다.(alias는 명령어를 변경-대체한다)
if [ -x /usr/bin/dircolors ]; then
    test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"
    alias ls='ls --color=auto'
    #alias dir='dir --color=auto'
    #alias vdir='vdir --color=auto'

    alias grep='grep --color=auto'
    alias fgrep='fgrep --color=auto'
    alias egrep='egrep --color=auto'
fi

# GCC 경고와 에러에 색상을 입힌다.
#export GCC_COLORS='error=01;31:warning=01;35:note=01;36:caret=01;32:locus=01:quote=01'

# 약간의 ls alias를 더한다
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'

# 길게 동작하는 명령들을 위해 "alert" alias(명령)을 추가한다.
#   sleep 10; alert
# 와 같이 사용한다.
alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e '\''s/^\s*[0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'

# Alias 정의들
# 당신은 여기의 디렉토리에 당신이 덧쓴것을 추가하는 대신에
# ~/.bash_aliases 와 같이 분리된 파일에 넣길 원할지도 모른다.
# bash-doc 패키지의 /usr/share/doc/bash-doc/examples 을 보아라

if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi

# 활성화된 프로그래밍 가능한 특징들
# ( /etc/bash.bashrc 그리고 /etc/profile 에서 이미 활성화되었다면 이것을 활성화할 필요는 없다.)
if ! shopt -oq posix; then
  if [ -f /usr/share/bash-completion/bash_completion ]; then
    . /usr/share/bash-completion/bash_completion
  elif [ -f /etc/bash_completion ]; then
    . /etc/bash_completion
  fi
fi

# bash prompt에 user-id와 현재 디렉토리를 표시할 수 있도록 변경
# \u는 사용자 이름을 표시
# \w는 현재 디렉토리 전체를 표시(\W는 현재 디렉토리의 최상위 디렉토리만 표시)
# \\$은 현재 사용가 uid가 0(root)이면 #을, 아니면 $을 표시
export PS1='[\u]\w \\$ '
