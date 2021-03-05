# Firewall-Classification-Engine
Instructions
Following is a programming exercise. The exercise consists of several checkpoints, that rely on each other. After every coding checkpoint, go over your code and make sure it is properly structured and organized.
Following the implementation, you will have a summary meeting with the interviewer - to go over the steps that were taken and code that was implemented. In addition, you might be asked to extend your solution with more features.
Provide meaningful logs in case unexpected behavior occurs during the program run (i.e. – invalid input).
You are encouraged to improve your solution, beyond the stated requirements. Please document what features were added if you decide to do so. Using a high-level programming language (Java/C#/Python) is recommended.
Your solution will be submitted for review via GitHub. You are encouraged to work with git throughout your development and to have branch/tag for each checkpoint.
Good luck!
Objective
1.
 Your mission is to design and implement a module in a Firewall server that decides whether to allow or deny incoming
 packets. write a program that receives the following command line arguments:
 A path to a text file - contains the list of Firewall rules.
 Each line of the file represents a rule, in the following format:
 <source-username>|<destination-ip-address>|<allow/deny>
a. The order of the rules determines the action to be taken. The action of the first rule that match will be taken. For example, in the below ruleset, packets to 1.2.3.4, from the user ‘mike@contoso.com’, should be allowed.
b. c.
d. You can assume IP addresses are all IPv4.
e. By default, if a packet does not match any rule, it should be allowed.
 Clarification: ‘allow’ does not mean ‘continue’, but simply chooses this action, for the given packet.
 If a line doesn’t fit the above format, ignore it and output a warning message.
 2. A path to a folder - contains text files, each representing a different source host going through the Firewall. a. The file name is the host’s name. In the file, each line represents an incoming packet, in the following format: <source-username>|<destination-ip-address>.
b. If a line doesn’t fit the above format, ignore it and output a warning message.
Required Output:
Your program should output the following log line for each packet: <host-name>: <username> access to <ip-address> was <allowed/denied>
 
  PERSONAL USE ONLY – DO NOT DISTRIBUTE
 Checkpoint 1
Implement the firewall classification engine according to the description above. Your firewall should receive a rules text file path and a folder with packets files. Your program should print the required output that described above.
Checkpoint 2
We extend our Firewall to support a few extensions to the rules: •
•
For example, this is a legitimate rules list:
** You should use a function that retrieve a subnet and IP and check if the IP is part of the subnet or not. for example, in Java you can use: org.apache.commons.net.util.SubnetUtils
Important: In your design take into consideration that in the future we would like to add more type of rules and we want the code to be easily extendable and maintainable as well.
  Joker usernames - In the username field, a ‘*’ joker can appear instead of a username, denoting all users
 Entire IP ranges - The IP part can come with a trailing subnet mask.
  * Notice that exact IPs can come in two forms:
 without a subnet mask (i.e. 1.2.3.4), and with an exact subnet mask (i.e. 1.2.3.4/32).
 
 
PERSONAL USE ONLY – DO NOT DISTRIBUTE
Checkpoint 3
Now, expand your program to support Firewall rules that accept domain names as well. For example, this is a legitimate rules list:
Notice: The incoming packets still contain IP addresses only (and not domains)
You will need to convert packet’s IP to domain name (and not vice versa).
Important: Take performance into consideration. Assume that your firewall should process a high volume of traffic.
