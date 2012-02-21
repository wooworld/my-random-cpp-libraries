#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <map>
#include <vector>
#include <string>
#include "DataSet.h"
#include "Document.h"

using namespace std;

class Classifier {
public:
  virtual void train( const DataSet& data ) = 0;
  virtual float test( const DataSet& data ) = 0;
  virtual unsigned int classify( const Document& doc ) = 0;  

protected:
  bool addVocab( const vector<Document>& docs, 
    map<string, unsigned int>& vocab );

  bool addVocab( const Document& doc, map<string, 
    unsigned int>& vocab );

  void tokenizeDocument( const Document& str,
    string delimiters,
    vector<string>& ignore,
    unsigned int minSize,
    vector<string>& split );

  unsigned int sumTokens( map<string, unsigned int>& vocab );

  vector<string> m_classes;
  map<string, unsigned int> m_vocab;
  vector< map<string, unsigned int> > m_classVocab;
};

#endif
