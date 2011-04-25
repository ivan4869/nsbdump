#include "iv_util.h"
#include "nsbdump.h"

int dumpb(const string &mapfname, const string &nsbfname){
  int fdnsm, fdmap, fdnsb;
  string nsmfname;
  map <unsigned, string> segmap; 
  map <unsigned, string>::iterator it_sm;
  vector <string> segvec;
  unsigned offset, tick;
  instruct_t op;
  
  nsmfname = nsbfname.substr(0, nsbfname.find(".nsb"));
  
  fdmap = iv::open_or_exit(mapfname, _O_RDONLY|_O_BINARY);
  fdnsb = iv::open_or_exit(nsbfname, _O_RDONLY|_O_BINARY);
  fdnsm = iv::open_or_exit(nsmfname, _O_CREAT|_O_TRUNC|_O_BINARY|_O_WRONLY, _S_IWRITE|_S_IREAD);

  while(iv::read(fdmap, &offset, sizeof(offset)) > 0){
    unsigned short len;
    char * segname;

    iv::read(fdmap, &len, sizeof(len));
    segname = new char[len];
    iv::read(fdmap, segname, len);

    segmap.insert(make_pair(offset, string(segname)));
    segvec.push_back(string(segname));

    delete [] segname;
  }

  it_sm = segmap.begin();
  while(iv::read(fdnsb, &op, sizeof(op)) > 0){
    unsigned short i = 0;
    unsigned tick = 0;

    while(i++ < op.cnt){
      unsigned short len;
      unsigned char * val;

      iv::read(fdnsb, &len, sizeof(len));
      val = new unsigned char[len];
      iv::read(fdnsb, val, len);


      delete [] val;
    }
      if(i != op.cnt){
        cerr << std::showbase << std::hex; 
        cerr << "Failed to deasm the nsb file at " << iv::tell(fdnsb) << endl;
        return -1;
      }
  }

  if(iv::eof(fdnsb))
    return 0;
  else{
    cerr << std::showbase << std::hex; 
    cerr << "Failed to deasm the nsb file at " << iv::tell(fdnsb) << endl;
    return -1;
  }
}
