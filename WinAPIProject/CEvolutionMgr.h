#pragma once

class CPokemon;
class CTexture;
class CEvolutionMgr
{
	SINGLE(CEvolutionMgr);
private:

	vector<wstring> PrePokemon;
	vector<int>			 LvupPokemon;
	vector<CPokemon*>	EvoPokemon;

	vector <CPokemon*> deletePokemon;
	
	CTexture*	m_prePokemon;
	CTexture*   m_EvoPokemon;

	bool		m_on;
	int			m_page;
public:
	void init();
	void update(CPokemon* _Pokemon, int _i);
	void render(HDC _dc);
	void SetEvoP(const wstring& _Pre, int _lv , CPokemon* _Evo);
};

