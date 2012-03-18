// 
// PROTOTYPES for Walking library
// 
void setForward();
void run(int speedClock);
int getDistanceFront();

void parse(char buff[])
{
	char delimiter[] = " ";
	char *cmd;
	char *val;
	char *i;
	
	cmd = strtok_r(buff, delimiter, &i);
	if (cmd == NULL) return; // No sense to proceed
	
	val = strtok_r(NULL, delimiter, &i);
	int value = 0;
	if (val != NULL)
	{
	   value = atoi(val);
	}
	
	if (strncmp(cmd, "FW", 2) == 0)
	{
	   setForward();
	   return;
	}
	
	if (strncmp(cmd, "DF", 2) == 0)
	{
	    getDistanceFront();
	    return;
	}
	
	if (strncmp(cmd, "RU", 2) == 0)
	{
	    run(value);
	    return;
	}
	
	Serial.print("? ");
	Serial.println(cmd);
}

void setForward()
{
	Serial.println("OK FW\n");
}

void run(int speedClock)
{
	Serial.print("OK RU ");
	Serial.println(speedClock);
}

int getDistanceFront()
{
	int dist = 33;
	Serial.println(dist);
	return dist;
}

void setup() {
  Serial.begin(9600);
  Serial.print("CMD: ");
}

char buffer[10];
int index;

void loop() {
	// PARSE COMMANDS
	while (Serial.available())
  	{
     char inChar = (char) Serial.read();
     if (index > sizeof(buffer)) {
        inChar = '\n';
        index = sizeof(buffer) - 1;
     }
     buffer[index] = inChar;
     index ++;

     if (inChar == '\n')
     {
        
       parse(buffer);
        index = 0;
	Serial.print("CMD: ");
     } 
   }
}
