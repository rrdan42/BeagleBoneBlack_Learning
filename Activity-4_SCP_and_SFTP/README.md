# SCP

`scp` is used to copy files to a remote device (over the network)

```
scp ./myfile.txt debian@192.168.7.2:/your/path/here
```

(Edit the path in above command)




# SFTP

To connect to the remote machine:
```
sftp username@hostname
```
e.g.
```
sftp debian@192.168.7.2
```

This will open the SFTP shell. 

## Copying a File from Localhost to Remote Machine
Run in the SFTP shell:
```
put filename
```

## Copying a File from Remote Machine to Localhost
Run in the SFTP shell:
```
get filename
```
