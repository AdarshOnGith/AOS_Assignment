#include <bits/stdc++.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;

void trackProgressUntilNow(double totalBytes, double dataReadNow) {
  static double totalDataRead = 0;
  totalDataRead += dataReadNow;
  totalDataRead = min(totalDataRead, totalBytes);
  int progress = ceil( (totalDataRead/(totalBytes*1.0))*100 );
  string ans = to_string( (progress) ) ;

  cout << "\rProgress : " + (ans) + " % ";
  cout.flush();
}

void makeDirAssignment1() {
    if (mkdir("Assignment1", 0700) == -1)
        cerr << "Failed to create directory. Because " << strerror(errno) << endl;
    else
        cout << "Directory created successfully." << endl; 

}

off_t checkAndRead(int filePtr, char* buffer, off_t readSize, int outputFilePtr) { 
  off_t status = read(filePtr, buffer, readSize);
  if(status == -1) {
    cerr << endl << "Error reading to the input file" << strerror(errno) << endl;
    close(filePtr);
    close(outputFilePtr);
    exit(EXIT_FAILURE);
  }
  return status;
}
off_t checkAndWrite(int outputFilePtr, string chunk, int filePtr) { 
  off_t status = write(outputFilePtr, chunk.data(), chunk.size());
  if(status == -1) {
    cerr << endl <<"Error writing to the output file" << strerror(errno) << endl;
    close(filePtr);
    close(outputFilePtr);
    exit(EXIT_FAILURE);
  }
  return status;
}
off_t checkAndSeek(int filePtr, off_t offset, int whence, int outputFilePtr) {
  off_t seekStatus = lseek(filePtr, offset, whence);
  if( seekStatus == -1 ) { 
    string activity = "beginning";
    if(whence == SEEK_END)
      activity = "end";
    else if(whence == SEEK_CUR)
      activity = "current position ";
    cerr << endl << "Error while seek from " + activity + " within the input file" << strerror(errno) << endl;
    close(filePtr);
    close(outputFilePtr);
    exit(EXIT_FAILURE);
  }
  return seekStatus;
}

void traverseFile(int flag, long long first, long long last, string ipFileName, string opFileName) {
    if(first > last) {
      cout << "Invalid input to index!" << endl; 
      return;
    }
    off_t chunkSize = 4069;
    makeDirAssignment1();

    int filePtr = open(ipFileName.data(), O_RDONLY);
    if (filePtr == -1) {
        cerr << endl  << "Error opening the Input file " + ipFileName + "! " << endl; 
        close(filePtr);
        exit(EXIT_FAILURE);
    } 

    int outputFilePtr = open("Assignment1/output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (outputFilePtr == -1) {
        cerr << endl  << "Error opening/creating the Output file " + opFileName + "! " << endl; 
        close(outputFilePtr);
        exit(EXIT_FAILURE);
    } 

    off_t sizeBytes = lseek(filePtr, 0, SEEK_END); //, filePtr);
    off_t sizeBytesFirst =  sizeBytes; 

    if(flag) {
      // lseek(filePtr, 0, SEEK_SET);
      sizeBytesFirst = checkAndSeek(filePtr, first, SEEK_SET, outputFilePtr);
      if(first >= sizeBytes || last >= sizeBytes) {
          cerr << endl << "Index are has invalid and greater than last index of file!" << endl;
          close(filePtr);
          close(outputFilePtr);
          exit(EXIT_FAILURE);
      }
    }  
    vector<char> buffer(chunkSize);
    cout << "The Buffer and Input/Output Files are ready to Operate " << endl;
    trackProgressUntilNow((double) sizeBytes, 0);

    for(off_t readPtr = sizeBytesFirst; readPtr > 0; readPtr -= chunkSize) {
        off_t readSize = min(chunkSize, static_cast<off_t>(readPtr));
        checkAndSeek(filePtr, (readPtr- readSize), SEEK_SET, outputFilePtr);
        checkAndRead(filePtr, buffer.data(), readSize, outputFilePtr);
        trackProgressUntilNow((double) sizeBytes, (double) readSize);
        string chunk(buffer.data(), readSize);
        reverse(chunk.begin(), chunk.end());
        checkAndWrite(outputFilePtr, chunk, filePtr);
    }
    
    if(flag && sizeBytesFirst < sizeBytes) {
      off_t sizeBytesLast  = checkAndSeek(filePtr, last, SEEK_SET, outputFilePtr);
      checkAndSeek(filePtr, first, SEEK_SET, outputFilePtr);
      
      for(off_t readPtr = sizeBytesFirst; readPtr <= sizeBytesLast; readPtr += chunkSize) {
        off_t readSize =  min(chunkSize, static_cast<off_t>((sizeBytesLast - readPtr) + 1));  
        checkAndRead(filePtr, buffer.data(), readSize, outputFilePtr);
        checkAndSeek(filePtr, (readPtr + readSize), SEEK_SET, outputFilePtr);
        trackProgressUntilNow((double) sizeBytes, (double) readSize);
        string chunk(buffer.data(), readSize);
        checkAndWrite(outputFilePtr, chunk, filePtr);
      }

      checkAndSeek(filePtr, 0, SEEK_END, outputFilePtr);
      for(off_t readPtr = sizeBytes; readPtr >= sizeBytesLast; readPtr -= chunkSize) {
        off_t readSize =  min(chunkSize, static_cast<off_t>(readPtr - (sizeBytesLast + 1))); 
        checkAndSeek(filePtr, (readPtr- readSize), SEEK_SET, outputFilePtr); 
        checkAndRead(filePtr, buffer.data(), readSize, outputFilePtr);
        trackProgressUntilNow((double) sizeBytes, (double) readSize);
        string chunk(buffer.data(), readSize);
        reverse(chunk.begin(), chunk.end());
        checkAndWrite(outputFilePtr, chunk, filePtr);
      }
    }
    trackProgressUntilNow((double) sizeBytes, 1);
    close(filePtr);
    close(outputFilePtr);
}

int main (int arg, char * argv[]) {
  long long start = 0, ed = 0;
  int flag = 0;
  if(!argv[1] || !argv[2] || arg < 3) {
    cerr << "Invalid Number of Arguments given as input!" << endl;
    return 0;
  }
  string inputFileName = argv[1];
  flag = stoi(argv[2]);
  if(flag) {
    start = stoi(argv[3]);
    ed = stoi(argv[4]);
  }

 
  if(start > ed || start < 0 || ed < 0)  {
    cerr << "Invalid Index given as input!" << endl;
  }
  else {
    string opFileName = "output.txt";
    traverseFile(flag, start, ed, inputFileName, opFileName);
  }
  cout << endl;
  return 0;
}