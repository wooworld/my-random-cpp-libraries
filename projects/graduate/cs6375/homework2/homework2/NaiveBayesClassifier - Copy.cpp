#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "NaiveBayesClassifier.h"
#include "stringHelp.h"

void NaiveBayesClassifier::train( const DataSet& data ) {
  // Add new vocab for all classes of documents in data.
  m_vocab.clear();
  for ( unsigned int i = 0; i < data.m_docs.size(); i++ ) {
    addVocab( data.m_docs[i], m_vocab );
  }

  // Copy class labels from data.
  m_classes.clear();
  for ( unsigned int i = 0; i < data.m_classes.size(); i++ ) {
    m_classes.push_back( data.m_classes[i].first );
  }

  // Count number of documents total.
  unsigned int numDocs = 0;
  for ( unsigned int i = 0; i < data.m_docs.size(); i++ ) {
    numDocs += data.m_docs[i].size();
  }

  m_prior.clear();
  m_classVocab.clear();
  for ( unsigned int i = 0; i < m_classes.size(); i++ ) {
    cout << "Working on class " << m_classes[i] << endl;
    // Update prior probabilities for each class.
    unsigned int numDocsThisClass = data.m_docs[i].size();    
    double prior = (double)numDocsThisClass / (double)numDocs;
    m_prior.push_back( prior );
    
    // Create class specific vocab.
    m_classVocab.resize( m_classVocab.size()+1 );   
    addVocab( data.m_docs[i], m_classVocab[i] );

    map<string, unsigned int>::iterator vocabIt;
    map<string, unsigned int>::iterator tokenLoc;
    vector<ConditionalProbabilityEntry>::iterator condProbLoc;

    for ( vocabIt = m_vocab.begin(); vocabIt != m_vocab.end(); vocabIt++ ) {
      // Get count of global token in class specific vocab.
      string token = vocabIt->first;
      //cout << "Updating w/ token " << token << endl;
      tokenLoc = m_classVocab[i].find( token );
      unsigned int tokenCount = (tokenLoc == m_classVocab[i].end()) ? 0 : tokenLoc->second;

      // Check for previous conditional probability entry.
      for ( condProbLoc = m_condProb.begin(); condProbLoc != m_condProb.end(); condProbLoc++ ) {
        if ( condProbLoc->m_label.compare( token ) == 0 ) {
          break;
        }
      }

      // Calculate update term for conditional probability entry.
      double numer = (double)tokenCount + 1.0;
      double denom = (double)sumTokens(m_classVocab[i]) + (double)m_vocab.size();

      //condProbLoc = find( m_condProb.begin(), m_condProb.end(), token );
      if ( condProbLoc == m_condProb.end() ) {
        ConditionalProbabilityEntry p;
        p.m_label = token;
        p.m_probs.resize( m_classes.size() );
        p.m_probs[i] = (numer / denom);
        m_condProb.push_back( p );
      }

      else {
        condProbLoc->m_probs[i] = (numer / denom);
      }
    }
  }

  // Print out the probabilities
  for ( unsigned int i = 0; i < m_condProb.size(); i++ ) {
    cout << m_condProb[i].m_label << endl;
    for ( unsigned int j = 0; j < m_condProb[i].m_probs.size(); j++ ) {
      cout << "[" << j << "]=" << m_condProb[i].m_probs[j] << endl;
    }
  }
}

void NaiveBayesClassifier::tokenizeDocument( const Document& doc, 
                                             string delimiters, 
                                             vector<string>& ignore,
                                             unsigned int minSize,
                                             vector<string>& split ) {
  split.clear();
  unsigned int lhs = 0;
  unsigned int rhs = doc.m_contents.find_first_of( delimiters, lhs );
  vector<string>::iterator it;

  while ( rhs != string::npos ) { 
    string token = doc.m_contents.substr( lhs, rhs-lhs );
    if ( token.length() >= minSize ) {
      it = find( ignore.begin(), ignore.end(), token ); 
      if ( it == ignore.end() ) {
        split.push_back( token );
      }      
    }
    lhs = rhs+1;
    rhs = doc.m_contents.find_first_of( delimiters, lhs );
  }
}

bool NaiveBayesClassifier::addVocab( const vector<Document>& docs, 
                                     map<string, unsigned int>& vocab ) {
  // Construct list of tokens to ignore.
  vector<string> tokensToIgnore;
  try {
    string tokenFileLoc = "../data/ignore.txt";
    #ifdef _WIN32
      tokenFileLoc = str_replace_all( tokenFileLoc, "/", "\\", ':' );
    #endif
    string line;
    ifstream tokenFile( tokenFileLoc.c_str() );
    
    while ( tokenFile.good() ) {
      getline( tokenFile, line );
      if ( line != "" ) {
        tokensToIgnore.push_back( line );
      }
    }
    tokenFile.close();
  }

  catch ( exception& e ) {
    cout << e.what() << endl;
    return false;
  }

  // Ignore any tokens < this length.
  const unsigned int minSize = 3;
  
  for ( unsigned int i = 0; i < docs.size(); i++ ) {
    vector<string> tokens;
    string delimiters = "\n -:;!@#$%^&*()=+[]{}<>,.?/\\\"'|";
    tokenizeDocument( docs[i], delimiters, tokensToIgnore, minSize, tokens );

    for ( unsigned int j = 0; j < tokens.size(); j++ ) {
      vocab[tokens[j]]++;
    }
  }

  return true;
}

unsigned int NaiveBayesClassifier::sumTokens( map<string, unsigned int>& vocab ) {
  map<string, unsigned int>::iterator it;
  unsigned int count = 0;
  for ( it = vocab.begin(); it != vocab.end(); it++ ) {
    count += (it->second);
  }
  return count;
}
