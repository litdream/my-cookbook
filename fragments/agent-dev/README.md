# Gemini Agent

## integrated

~/.gemini/command/weather.toml


### snow-accumulation

So, if it is snowing, I want  weather agent calculates  snow accumulation agent.  We can write snow-accumulation agent embedding weather curl command,  But,  I would like to test pipe.   So, weather agent will read  weather data,  and determine, if there is any snow in 24 hours.   If it sees snow in 24 hours,  it passes its weather data to  snow-accumulation agent.   This agent will process this data (without curl command, but using weather agent data),  calculate accumulation in 3 hours window, and determine which is the best time to go out to shovel, ( threshold is greather than 5 inch ).

