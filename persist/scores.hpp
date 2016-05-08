#ifndef _SCORES_H_
#define _SCORES_H_
#define SOCKET_UNIX
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstring>
#include<algorithm>
#include<sstream>
#include<cctype>
#include<cstdlib>
#include"persist.hpp"
#ifdef SOCKET_UNIX
#include"socket.hpp"
#endif




std::string URL_encode(const std::string text) {
	std::ostringstream ss;
	unsigned int i;
	for(i = 0; i < text.length(); ++i) {
		if(text[i] == ' ') {
			ss << "+";
			continue;
		}
		else if(isalnum(text[i]) || text[i] == '-' || text[i] == '_' || text[i] == '.') {
			ss << text[i];
			continue;
		}
		else {
			char dat[256];
			snprintf(dat, 255, "%%%02X", static_cast<unsigned int>(text[i]));
			ss << dat;
		}
	}
	return ss.str();
}

struct Score {
    char username[25];
    unsigned int score;

    Score() {
    	score = 0;
    }

    Score(int x) {
    	score = x;
    }

    Score(const Score &s) {
    	score = 0;
    	this->operator=(s);
    }
    void operator=(const Score &s) {
    	score=s.score;
    	snprintf(username,25,"%s", s.username);
    }
    Score(const char *userName, unsigned int score) {
    	this->score = score;
    	snprintf(username,25,"%s", userName);
    }

    friend bool operator<(const Score &s1, const Score &s2);
    friend std::ostream &operator<<(std::ostream &out, const Score &s);
};


// sort in reverse order
bool operator<(const Score &s1, const Score &s2) {
	if(s1.score > s2.score) return true;
	return false;
}

std::ostream &operator<<(std::ostream &out, const Score &score) {
	out << score.score << ": " << score.username;
	return out;
}


void readFunction(std::vector<Score> &value) {
    std::fstream file_ptr;

    file_ptr.open("scores.dat", std::ios_base::binary | std::ios_base::in);
    
    if(file_ptr.is_open()) {
    	int index = 0;
    	while(!file_ptr.eof() && index <= 9) {
    		Score scr;
    		file_ptr.read(reinterpret_cast<char*>(&scr), sizeof(scr));
    		if(scr.score!=0)
    		value.push_back(scr);
    		++index;
    	}
        file_ptr.close();
    }
}
void writeFunction(std::vector<Score> &value) {
    std::fstream file_ptr;
    file_ptr.open("scores.dat", std::ios::binary | std::ios::out);
    int index = 0;

    for(auto i = value.begin(); i != value.end() && (index <= 9); ++i) {
    	Score &score = *i;
    	if(score.score != 0)
     	file_ptr.write(reinterpret_cast<char*>(&score), sizeof(score));
     	++index;
    }
    file_ptr.close();
 }

class ScoreException : std::exception {
public:
	virtual const char *what() const throw() { return "No scores in file."; }
};

class ScoreBoard {
public:
    ScoreBoard() : scores(std::vector<Score>(), readFunction, writeFunction) {}
    ScoreBoard(const ScoreBoard &b) = delete;
    ScoreBoard(ScoreBoard&&) = delete;
    void operator=(const ScoreBoard &b) = delete;
    bool enterUser(const char *src,const unsigned int score) {
    	std::vector<Score>::iterator offset;
    	for(offset=scores.get().begin(); offset!=scores.get().end(); ++offset) {
    		if(std::string(src)==std::string(offset->username)) {
    			if(score > offset->score) {
    				offset->score = score;
    				std::sort(scores.get().begin(), scores.get().end());
    				return true;
    			}
    			std::cout << "Score lower than other entry...\n";
    			return false;
    		}
    	}
    	if(scores.get().size() > 9) {
    		Score &s = scores.get()[scores.get().size()-1];
    		if(s.score > score) return false;
    		else {
    			s.score = score;
    			snprintf(s.username,25,"%s", src);
    			std::sort(scores.get().begin(), scores.get().end());
    			return true;
    		}
    	}
    	else {
    		scores.get().push_back(Score(src, score));
    		std::sort(scores.get().begin(), scores.get().end());
    		return true;
    	}
    	return false;
    }
    void DisplayScores(bool dir = true) {
    	if(dir == true)
    	std::copy(scores.get().begin(), scores.get().end(), std::ostream_iterator<Score>(std::cout, "\n"));
    	else
    	std::copy(scores.get().rbegin(), scores.get().rend(), std::ostream_iterator<Score>(std::cout, "\n"));
    }
    Score &operator[](unsigned int pos) { return scores.get()[pos]; }
    Score &at(unsigned int pos) { return scores.get().at(pos); }
    int size() { return scores.get().size(); }

    Score &highestScore() throw(ScoreException) {
    	if(scores.get().size() <= 0)
    		throw ScoreException();
    	return scores.get()[0];
    }
protected:
    persist<std::vector<Score>> scores;
};

class SendScore {
	ScoreBoard *scoreBoard;
public:
	explicit SendScore(ScoreBoard *scoreb) : scoreBoard(scoreb) {}
	virtual ~SendScore() {	}
	virtual void sendData(const Score &s) = 0;
	virtual void init(const std::string iptext,const unsigned int port_num) = 0;
	virtual void close() = 0;

	void operator()() {
		if(scoreBoard->size()>0)
		sendData(scoreBoard->at(0));
	}
};

class TempSocketObject {
protected:
	mx::mxSocket sock_obj;
public:
	TempSocketObject() {
		sock_obj.createSocket();
	}
	void initConnection(const std::string ip,const unsigned int port) {
		bool op;
		if(ip.length()>0 && isdigit(ip[0])) {
			 op = sock_obj.connectTo(ip, port);
		} else op = sock_obj.connectTo(mx::getHost(ip), port);
		// send data about post
		if(op == false) {
			std::cerr << "Failed connection to: " << ip << " [" << mx::getHost(ip) << "] " << ":" << port << std::endl;
		} else {
			std::cout << "Successful connection to: " << ip << " [" << mx::getHost(ip) << "]\n";
		}
	}
	unsigned int Write(void *buf,const unsigned int s) {
		std::cout << "Writing...  " << s << "\n";
		return sock_obj.Write(buf, s);
	}
	unsigned int Read(void *buf, const unsigned int s) {
		return sock_obj.Read(buf, s);
	}
	void Close() {
		sock_obj.closeSocket();
		std::cout << "socket closed..\n";
	}
	void SendString(std::string text) {
		const char *src = text.c_str();
		unsigned int len = text.length();
		Write(const_cast<char*>(src), len);
	}
};

class SendObject : public SendScore {
	TempSocketObject tsocket;
public:

	virtual ~SendObject() {	}

	SendObject(ScoreBoard *score) : SendScore(score) {

	}

	virtual void init(const std::string iptext,const unsigned int port_num) {
		tsocket.initConnection(iptext, port_num);
	}
	virtual void close() {
		tsocket.Close();
	}
	virtual void sendData(const Score &s) {
		std::ostringstream stream, buffer_str;
		unsigned int content_length=0;
		buffer_str << "user_name=" << URL_encode(s.username) << "&score=" << s.score << "\n\n";
		content_length = buffer_str.str().size();
		stream << "POST /high_score.php HTTP/1.0\nFrom: user@lostsidedead.com\nUser-Agent: MUTSCORE/1.0\nContent-Type: application/x-www-form-urlencoded\nContent-Length: " <<
				content_length << "\n\n" << buffer_str.str();
		std::cout << "Sending ... " << stream.str() << std::endl;
		tsocket.SendString(stream.str());
		std::string total;
		size_t offset = 0;

		while(1) {
			static char buf[1024];
			offset = tsocket.Read(buf, 1023);
			if(offset == 0) break;
			buf[offset] = 0;
			total+=buf;
		}
		std::cout << "Response: ...: " << total << "\n";
	}

	void operator()() {
		sendAll();
	}

	void sendAll() {
		init("lostsidedead.com", 80);
		SendScore::operator()();
		close();
	}
};

#endif




