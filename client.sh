#!/bin/bash

# fifo pipes
client_pipe=/tmp/client"$BASHPID"
server_pipe=/tmp/server

# interface with server
getLedState=get-led-state
setLedState=set-led-state

getLedColor=get-led-color
setLedColor=set-led-color

getLedRate=get-led-rate
setLedRate=set-led-rate


trap "rm -f $client_pipe" EXIT

if [[ ! -p $client_pipe ]]; then
    mkfifo $client_pipe
fi

send_request () {
    echo "$BASHPID" $1 $2 > $server_pipe
}

read_from_pipe(){
    if read line <$client_pipe; then
        echo $line
    fi
}

show_power_state() {
    send_request $getLedState
    sleep 0.001
    if read line <$client_pipe; then
        echo $line
        state=$(echo $line|sed -n 's/[A-Z]* \([a-z]*\)$/\1/p')
        if [[ ! -z "$state" ]] ; then
            echo Current power state is $state
        else
            echo Current power state is unknown
        fi
    else
        echo Something wrong while reading pipe
    fi
}

setPowerState() {
    send_request $setLedState $1
    sleep 0.001
    read_from_pipe
}

show_power_menu() {
    while true; do
    options=("Power set enable" "Power set disable" "Return to previous menu")
    show_power_state
    echo "Choose an option: "
    select opt in "${options[@]}"; do
        case $REPLY in
            1) setPowerState on; break ;;
            2) setPowerState off; break ;;
            3) break 2 ;;
            *) echo invalid option $REPLY
        esac
    done
done
}

show_color() {
    send_request $getLedColor
    sleep 0.001
    if read line <$client_pipe; then
        color=$(echo $line|sed -n 's/[A-Z]* \([a-z]*\)$/\1/p')
        if [[ ! -z "$color" ]] ; then
            echo Current color is $color
        else
            echo Current color is unknown
        fi
    fi
}

setColor() {
    send_request $setLedColor $1
    read_from_pipe
}

show_color_menu() {
    while true; do
    options=("Red" "Green" "Blue" "Return to previous menu")
    show_color
    echo "Choose an option: "
    select opt in "${options[@]}"; do
        case $REPLY in
            1) setColor red; break ;;
            2) setColor green; break ;;
            3) setColor blue; break ;;
            4) break 2 ;;
            *) echo invalid option $REPLY
        esac
    done
done
}

show_rate() {
    send_request $getLedRate
    sleep 0.001
    if read line <$client_pipe; then
        ledRate=$(echo $line|sed -n 's/[A-Z]* \([0-9]*\)$/\1/p')
        if [[ ! -z "$ledRate" ]] ; then
            echo Current ledRate is $ledRate
        else
            echo Current ledRate is unknown
        fi
    fi
}

show_rate_menu() {
    show_rate
    echo "set led blink rate "

    read rate
    if [[ "$rate" =~ ^[0-5]$ ]];
    then 
        send_request $setLedRate $rate

        if read line <$client_pipe; then
                echo $line
        fi
    else
        echo "Error: expect digit 0..5"
    fi

}

while true; do
    options=("Change power state" "Change color" "Change led rate" "Quit")
    echo "Choose an option: "
    select opt in "${options[@]}"; do
        case $REPLY in
            1) show_power_menu; break ;;
            2) show_color_menu; break ;;
            3) show_rate_menu; break ;;
            4) break 2 ;;
            *) echo invalid option $REPLY
        esac
    done
done
echo 'Thank you for using our product. Bye bye!'

